#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/timer.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/fs.h>
#include <linux/i2c.h>

#define DEVICE_NAME		"lightBH1750"	/* 名字 	*/

#define LIGHTLISTMAX 16

/* light_sensor设备结构体 */

struct light_sensor_dev {
	dev_t devid;			/* 设备号 	 */
	struct cdev cdev;		/* cdev 	*/
	struct class *class;	/* 类 		*/
	struct device *device;	/* 设备 	 */
	int major;			/* 主设备号 */
	struct timer_list timer;/* 定义一个定时器*/

	void *pI2C_clinet;	/* i2c client */
	int errTimes;
	int lightList[LIGHTLISTMAX];
	int lightListIndex;
	int bFullList;
	int curLight;
	//struct _powerlimit powerlimit;
	struct fasync_struct *async_queue;		/* 异步相关结构体 */
};

struct light_sensor_dev device;		/* 设备 */

/************************************************************************/
/* sysfs                                                                */
/************************************************************************/
static ssize_t lightBH1750_sysfs_show_curLight(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d", device.curLight);
}

static DEVICE_ATTR(curLight, S_IRUGO, lightBH1750_sysfs_show_curLight, NULL);

static struct attribute *lightBH1750_attrs[] = {
	&dev_attr_curLight.attr,
	NULL
};

static const struct attribute_group lightBH1750_sysfs_files = {
	.attrs = lightBH1750_attrs,
};
/************************************************************************/
/*                                                                      */
/************************************************************************/

/* @description	: 定时器服务函数，用于按键消抖，定时器到了以后
*				  再次读取按键值，如果按键还是处于按下状态就表示按键有效。
* @param - arg	: 设备结构变量
* @return 		: 无
*/
void timer_function(unsigned long arg)
{
	int retry=3,i;
	struct light_sensor_dev *dev = (struct light_sensor_dev *)arg;
	__be16 light;
	unsigned long lx;
	int ret;
	unsigned char cmd[1] = { 0x20 };	
	dev->timer.data = (unsigned long)dev;
	mod_timer(&dev->timer, jiffies + msecs_to_jiffies(1000));	/* 1s定时 */
	while(retry!=0)
	{
		//0x20,1 lx 分辨率，120ms测量时间，测量后自动power down
		ret = i2c_master_send(dev->pI2C_clinet, cmd, 1);
		if (ret < 0) 
		{
			retry--;
			continue;
		}
		mdelay(150);
		ret = i2c_master_recv(dev->pI2C_clinet, (char *)&light, 2);              //接收两个字节数据，先接收高八位，后接收低八位
		if (ret < 0) 
		{
			retry--;
			continue;
		}
		break;
	}
	if (retry != 0)//成功读取
	{
		dev->lightList[dev->lightListIndex++] = be16_to_cpu(light);
		dev->errTimes = 0;
		if (dev->bFullList != 0)
		{
			if (dev->lightListIndex == LIGHTLISTMAX)
				dev->lightListIndex = 0;
			lx = 0;
			for (i = 0; i < LIGHTLISTMAX; i++)
				lx += dev->lightList[i];
			//lx=lx/16/1.2   lx=lx*5/16/6
			lx = lx * 5;
			lx = lx / LIGHTLISTMAX;
			lx = lx / 6;
			dev->curLight = lx;
			if (dev->async_queue)
				kill_fasync(&dev->async_queue, SIGIO, POLL_IN);	/* 释放SIGIO信号 */
		}
		else
		{
			if (dev->lightListIndex == LIGHTLISTMAX-1)
			{
				dev->bFullList = 1;
			}
		}	
	}
	else//读取失败
	{
		dev->errTimes++;
		printk("light_wf:read bh1750 fail : %d!!\n", dev->errTimes);
		if (dev->async_queue)
		{
			kill_fasync(&dev->async_queue, SIGIO, POLL_ERR);
		}
		
	}	
	
}

/*
* @description		: 打开设备
* @param - inode 	: 传递给驱动的inode
* @param - filp 	: 设备文件，file结构体有个叫做private_data的成员变量
* 					  一般在open的时候将private_data指向设备结构体。
* @return 			: 0 成功;其他 失败
*/
static int device_open(struct inode *inode, struct file *filp)
{
	filp->private_data = &device; /* 设置私有数据 */
	return 0;
}

/*
* @description     : 从设备读取数据
* @param - filp    : 要打开的设备文件(文件描述符)
* @param - buf     : 返回给用户空间的数据缓冲区
* @param - cnt     : 要读取的数据长度
* @param - offt    : 相对于文件首地址的偏移
* @return          : 读取的字节数，如果为负值，表示读取失败
*/
static ssize_t device_read(struct file *filp, char __user *buf, size_t cnt, loff_t *offt)
{
	int ret;
	struct light_sensor_dev *dev = (struct light_sensor_dev *)filp->private_data;
	ret = copy_to_user(buf, &dev->curLight, sizeof(dev->curLight));
	if (ret < 0)
		printk(KERN_EMERG "light_wf:device read error : %d!!\n", ret);
	return 0;
}

/*
* @description		: 向设备写数据
* @param - filp 	: 设备文件，表示打开的文件描述符
* @param - buf 	: 要写给设备写入的数据
* @param - cnt 	: 要写入的数据长度
* @param - offt 	: 相对于文件首地址的偏移
* @return 			: 写入的字节数，如果为负值，表示写入失败
*/
static ssize_t device_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *offt)
{
	// 	int retvalue;
	// 	unsigned char databuf[1];
	// 	unsigned char beepstat;
	// 	struct light_sensor_dev *dev = filp->private_data;
	// 
	// 	retvalue = copy_from_user(databuf, buf, cnt);
	// 	if (retvalue < 0) {
	// 		printk("kernel write failed!\r\n");
	// 		return -EFAULT;
	// 	}
	// 
	// 	beepstat = databuf[0];		/* 获取状态值 */
	// 	if (beepstat == BEEPON) {
	// 		gpio_set_value(dev->pulsegpio, 0);	/* 打开蜂鸣器 */
	// 	}
	// 	else if (beepstat == BEEPOFF) {
	// 		gpio_set_value(dev->pulsegpio, 1);	/* 关闭蜂鸣器 */
	// 	}
	return 0;
}
/*
* @description		: ioctl函数，
* @param - filp 	: 要打开的设备文件(文件描述符)
* @param - cmd 	: 应用程序发送过来的命令
* @param - arg 	: 参数
* @return 			: 0 成功;其他 失败
*/
static long device_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	//struct light_sensor_dev *dev = (struct light_sensor_dev *)filp->private_data;
	//switch (cmd) {
 //	case ioctlcmd_ResetPulseCount:		/* 关闭定时器 */
 //		dev->pulseCount.count = 0;
 //		SavePulseCount(dev->pulseCount.buf);
 //		break;
 //	case ioctlcmd_ResetCalcPower:		/* 打开定时器 */
 //		dev->bFistCalcPulse = 1;
 //		dev->CalcPulseCount = 0;
 //		break;
	//default:
	//	break;
	//}
	return 0;
}

/*
* @description     : fasync函数，用于处理异步通知
* @param - fd		: 文件描述符
* @param - filp    : 要打开的设备文件(文件描述符)
* @param - on      : 模式
* @return          : 负数表示函数执行失败
*/
static int device_fasync(int fd, struct file *filp, int on)
{
	struct light_sensor_dev *dev = (struct light_sensor_dev *)filp->private_data;
	return fasync_helper(fd, filp, on, &dev->async_queue);
}
static int device_release(struct inode *inode, struct file *filp)
{
	return device_fasync(-1, filp, 0);
}
/* 设备操作函数 */
static struct file_operations device_fops = {
	.owner = THIS_MODULE,
	.open = device_open,
	.write = device_write,
	.read = device_read,
	.unlocked_ioctl = device_unlocked_ioctl,
	.fasync = device_fasync,
	.release = device_release
};

/*
* @description     : flatform驱动的probe函数，当驱动与
*                    设备匹配以后此函数就会执行
* @param - dev     : platform设备
* @return          : 0，成功;其他负值,失败
*/
static int device_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int rc = 0;

	printk("light_wf:light_sensor driver and device was matched!\r\n");
	printk("light_wf:client name : %s,%ld\r\n",client->name,id->driver_data);
	/* 1、构建设备号 */
	alloc_chrdev_region(&device.devid, 0, 1, DEVICE_NAME);
	device.major = MAJOR(device.devid);
	/* 2、注册设备 */
	cdev_init(&device.cdev, &device_fops);
	cdev_add(&device.cdev, device.devid, 1);

	/* 3、创建类 */
	device.class = class_create(THIS_MODULE, DEVICE_NAME);
	if (IS_ERR(device.class)) {
		return PTR_ERR(device.class);
	}
	/* 4、创建设备 */
	device.device = device_create(device.class, NULL, device.devid, NULL, DEVICE_NAME);
	if (IS_ERR(device.device)) {
		return PTR_ERR(device.device);
	}

	device.pI2C_clinet = client;
	/* 创建定时器 */
	init_timer(&device.timer);
	device.timer.function = timer_function;
	rc = sysfs_create_group(&client->dev.kobj, &lightBH1750_sysfs_files);
	if (rc)
		return rc;
	return 0;
}

/*
* @description     : platform驱动的remove函数，移除platform驱动的时候此函数会执行
* @param - dev     : platform设备
* @return          : 0，成功;其他负值,失败
*/
static int device_remove(struct i2c_client *client)
{
	sysfs_remove_group(&client->dev.kobj, &lightBH1750_sysfs_files);
	del_timer_sync(&device.timer);	/* 删除定时器 */
									/* 释放中断 */
									/* 删除设备 */
	cdev_del(&device.cdev);
	unregister_chrdev_region(device.devid, 1);
	/* 注销掉类和设备 */
	device_destroy(device.class, device.devid);
	class_destroy(device.class);
	return 0;
}
/* 传统匹配方式ID列表 */
static const struct i2c_device_id device_id[] = {
	{ "BH1750", 100 },
	{}
};
//i2c client name 将是BH1750
//经测试，应为“，”后面的，即器件型号
/* 匹配列表 */
static const struct of_device_id device_of_match[] = {
	{ .compatible = "ROHM,BH1750" },
	{ /* Sentinel */ }
};

/* platform驱动结构体 */
static struct i2c_driver driver = {
	.driver = {
		.owner = THIS_MODULE,
		.name = "light_sensor_BH1750",         /* 驱动名字，用于和设备匹配 */
		.of_match_table = device_of_match, /* 设备树匹配表          */
		},
	.probe = device_probe,
	.remove = device_remove,
	.id_table = device_id,
};

/*
* @description	: 驱动出口函数
* @param 		: 无
* @return 		: 无
*/
static int __init light_sensor_init(void)
{
	device.errTimes = 0;
	device.lightListIndex = 0;
	device.curLight = 0;
	device.bFullList = 0;
	/* 创建定时器 */
	init_timer(&device.timer);
	device.timer.function = timer_function;
	device.timer.data = (unsigned long)&device;
	mod_timer(&device.timer, jiffies + msecs_to_jiffies(1000));	/* 1s定时 */
	return i2c_add_driver(&driver);
}

/*
* @description	: 驱动出口函数
* @param 		: 无
* @return 		: 无
*/
static void __exit light_sensor_exit(void)
{
	i2c_del_driver(&driver);
}

module_init(light_sensor_init);
module_exit(light_sensor_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("hrbeu wangf0228");
