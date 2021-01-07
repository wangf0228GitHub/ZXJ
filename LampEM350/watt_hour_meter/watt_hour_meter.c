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
#define DEVICE_NAME		"watt_hour_meter"	/* 名字 	*/
#define DEVICE_MINOR	100			/* 子设备号 */


struct _powerlimit {
	unsigned int PowerUp;
	unsigned int PowerDown;
};

#define ioctlcmd_ResetPulseCount	(_IO('w', 0x1))	
#define ioctlcmd_ResetCalcPower		(_IO('w', 0x2))

#define CalcPulseMax 10
#define CalcConst (int)(9000*CalcPulseMax*1000)//1度电400个秒冲,每个脉冲9000J
/* watt_hour_meter设备结构体 */
typedef union {
	int count;
	unsigned char buf[4];
}_PulseCount;
struct watt_hour_meter_dev {
//	dev_t devid;			/* 设备号 	 */
// 	struct cdev cdev;		/* cdev 	*/
// 	struct class *class;	/* 类 		*/
// 	struct device *device;	/* 设备 	 */
	struct device_node	*nd; /* 设备节点 */
	int pulsegpio;			/* 脉冲所使用的GPIO编号		*/
	struct timer_list timer;/* 定义一个定时器*/
	int irqnum;				/* 中断号     */
	
	_PulseCount pulseCount;
	int bCalcPower;
	int bFistCalcPulse;
	int CalcPulseCount;
	unsigned long  start_jiffies;
	unsigned long  end_jiffies;
	int curPower;
	//struct _powerlimit powerlimit;
	struct fasync_struct *async_queue;		/* 异步相关结构体 */
};

struct watt_hour_meter_dev device;		/* 设备 */
/************************************************************************/
/* file                                                                 */
/************************************************************************/
#define MY_FILE  "/home/root/LampEM350/watt_hour_meter.log"
static int SavePulseCount(unsigned char *pBuf)
{
	int result = 0;
	int len = 4;
	loff_t pos;
	struct file* filp = NULL;
	mm_segment_t old_fs;
	filp = filp_open(MY_FILE, O_RDWR | O_CREAT, 0777); //创建文件
	if (IS_ERR(filp))
	{
		printk(KERN_EMERG "watt_wf:no file!!\n");
	}
	else
	{
		old_fs = get_fs();
		set_fs(KERNEL_DS);
		pos = 0;
		result = vfs_write(filp, pBuf, len, &pos);
		if (result > 0)
		{
			//printk("watt_wf:write data:%d \n", result);
		}
		else
		{
			printk(KERN_EMERG "watt_wf:write err:%d \n", result);
		}
		set_fs(old_fs);
		filp_close(filp, NULL);
	}
	return 0;
}

static int InitPulseCount(unsigned char *pBuf)
{
	int result = 0;
	int len = 4, i;
	loff_t pos;
	struct file* filp = NULL;
	mm_segment_t old_fs;
	filp = filp_open(MY_FILE, O_RDWR | O_CREAT, 0777); //创建文件
	if (IS_ERR(filp))
	{
		printk(KERN_EMERG "watt_wf:no file!!\n");
	}
	else
	{
		old_fs = get_fs();
		set_fs(KERNEL_DS);
		pos = 0;
		result = vfs_read(filp, pBuf, len, &pos);
		if (result > 0)
		{
			//printk("watt_wf:read data:%d \n", result);
		}
		else
		{
			printk("watt_wf:read err:%d \n", result);
			for (i = 0; i < len; i++)
				pBuf[i] = 0;
			result = vfs_write(filp, pBuf, len, &pos);
			if (result > 0)
			{
				printk("watt_wf:write data:%d \n", result);
			}
			else
			{
				printk(KERN_EMERG "watt_wf:write err:%d \n", result);
			}
		}
		set_fs(old_fs);
		filp_close(filp, NULL);
	}
	return 0;
}
/************************************************************************/
/* sysfs                                                                */
/************************************************************************/
static ssize_t watt_hour_meter_sysfs_show_pulseCount(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d", device.pulseCount.count);
}

static DEVICE_ATTR(pulseCount, S_IRUGO, watt_hour_meter_sysfs_show_pulseCount, NULL);

static ssize_t watt_hour_meter_sysfs_show_curPower(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d", device.curPower);
}

static DEVICE_ATTR(curPower, S_IRUGO, watt_hour_meter_sysfs_show_curPower, NULL);

static struct attribute *watt_hour_meter_attrs[] = {
	&dev_attr_pulseCount.attr,
	&dev_attr_curPower.attr,
	NULL
};

static const struct attribute_group watt_hour_meter_sysfs_files = {
	.attrs = watt_hour_meter_attrs,
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
struct tasklet_struct tasklet_pulse;
/* tasklet 处理函数 */
void tasklet_pulse_func(unsigned long data)
{
	/* tasklet 具体处理内容 */
	unsigned int power_ms;
	struct watt_hour_meter_dev* pDevice = (struct watt_hour_meter_dev*)data;
	pDevice->pulseCount.count++;
	SavePulseCount(pDevice->pulseCount.buf);
	if(pDevice->bCalcPower)
	{
		if (pDevice->CalcPulseCount == CalcPulseMax)//测量完成，开始计算
		{
			power_ms = jiffies_to_msecs(pDevice->end_jiffies - pDevice->start_jiffies);
			pDevice->curPower = CalcConst / power_ms;
			printk("watt_wf:current power is %d ms -> %d w\n", power_ms, pDevice->curPower);
			pDevice->CalcPulseCount = 0;
			pDevice->bFistCalcPulse = 1;
			if (pDevice->async_queue)
				kill_fasync(&pDevice->async_queue, SIGIO, pDevice->curPower);	/* 释放SIGIO信号 */
		}
	}
	printk("watt_wf:pulse count is %d \n", pDevice->pulseCount.count);
}

/* @description		: 中断服务函数，开启定时器，延时10ms，
*				  	  定时器用于脉冲消抖。
* @param - irq 	: 中断号
* @param - dev_id	: 设备结构。
* @return 			: 中断执行结果
*/
static irqreturn_t irqhandler_pulse(int irq, void *dev_id)
{
	struct watt_hour_meter_dev *dev = (struct watt_hour_meter_dev *)dev_id;
	dev->timer.data = (volatile long)dev_id;
	mod_timer(&dev->timer, jiffies + msecs_to_jiffies(10));	/* 10ms定时 */
	//printk("watt_wf:io irq\r\n");
	return IRQ_RETVAL(IRQ_HANDLED);
}
/* @description	: 定时器服务函数，用于按键消抖，定时器到了以后
*				  再次读取按键值，如果按键还是处于按下状态就表示按键有效。
* @param - arg	: 设备结构变量
* @return 		: 无
*/
void timer_function(unsigned long arg)
{
	unsigned char value;
	struct watt_hour_meter_dev *dev = (struct watt_hour_meter_dev *)arg;
	value = gpio_get_value(dev->pulsegpio); 	/* 读取IO值 */
	if (value == 0)
	{
		if (dev->bCalcPower != 0)//需要计算功率
		{
			if (dev->bFistCalcPulse != 0)//计算功率的第一个脉冲
			{
				dev->bFistCalcPulse = 0;
				dev->CalcPulseCount = 0;
				dev->start_jiffies = jiffies;
			}
			else
			{
				if (dev->CalcPulseCount < CalcPulseMax)
				{
					dev->CalcPulseCount++;
					if (dev->CalcPulseCount == CalcPulseMax)
					{
						dev->end_jiffies = jiffies;
					}
				}
			}
		}
		tasklet_schedule(&tasklet_pulse);
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
 	struct watt_hour_meter_dev *dev = (struct watt_hour_meter_dev *)filp->private_data;
	ret=copy_to_user(buf, dev->pulseCount.buf, 4);
	if (ret < 0)
		printk(KERN_EMERG "watt_wf:device read error : %d!!\n", ret);
	ret = copy_to_user(buf+4, &dev->curPower, sizeof(dev->curPower));
	if (ret < 0)
		printk(KERN_EMERG "watt_wf:device read error : %d!!\n", ret);
// 	printk("watt_wf:device read error : %d!!\n", dev->pulseCount.count);
// 	printk("watt_wf:%02x %02x %02x %02x\n", dev->pulseCount.buf[0], dev->pulseCount.buf[1], dev->pulseCount.buf[2], dev->pulseCount.buf[3]);
// 	printk("watt_wf:%p\n%p\n", &dev->pulseCount.count, &dev->pulseCount.buf);
	
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
// 	struct watt_hour_meter_dev *dev = filp->private_data;
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
	struct watt_hour_meter_dev *dev = (struct watt_hour_meter_dev *)filp->private_data;
	switch (cmd) {
	case ioctlcmd_ResetPulseCount:		/* 关闭定时器 */
		dev->pulseCount.count=0;
		SavePulseCount(dev->pulseCount.buf);
		break;
	case ioctlcmd_ResetCalcPower:		/* 打开定时器 */
		dev->bFistCalcPulse = 1;
		dev->CalcPulseCount = 0;
		break;
	default:
		break;
	}
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
	struct watt_hour_meter_dev *dev = (struct watt_hour_meter_dev *)filp->private_data;
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
	.read=device_read,
	.unlocked_ioctl= device_unlocked_ioctl,
	.fasync = device_fasync,
	.release = device_release
};

/* MISC设备结构体 */
static struct miscdevice watt_hour_meter_miscdev = {
	.minor = DEVICE_MINOR,
	.name = DEVICE_NAME,
	.fops = &device_fops,
};
/*
* @description     : flatform驱动的probe函数，当驱动与
*                    设备匹配以后此函数就会执行
* @param - dev     : platform设备
* @return          : 0，成功;其他负值,失败
*/
static int device_probe(struct platform_device *dev)
{
	int ret = 0;
	printk("watt_wf:watt_hour_meter driver and device was matched!\r\n");
	/* 设置watt_hour_meter所使用的GPIO */
	/* 1、获取设备节点：watt_hour_meter */
	device.nd = of_find_node_by_path("/watt_hour_meter");
	if (device.nd == NULL) {
		printk("watt_wf:watt_hour_meter node not find!\r\n");
		return -EINVAL;
	}

	/* 2、 获取设备树中的gpio属性*/
	device.pulsegpio = of_get_named_gpio(device.nd, "pulsegpio", 0);
	if (device.pulsegpio < 0) {
		printk("watt_wf:can't get pulsegpio");
		return -EINVAL;
	}

	/* 3、设置GPIO5_IO01为输出，并且输出高电平，默认关闭BEEP */
	ret=gpio_request(device.pulsegpio, "PowerPulse");	/* 请求IO */
	if (ret < 0) {
		printk("watt_wf:can't request gpio!\r\n");
	}
	ret = gpio_direction_input(device.pulsegpio);
	if (ret < 0) {
		printk("watt_wf:can't input gpio!\r\n");
	}
	device.irqnum = gpio_to_irq(device.pulsegpio);
	ret = request_irq(device.irqnum, irqhandler_pulse,
		IRQF_TRIGGER_FALLING, DEVICE_NAME, &device);
	if (ret < 0) {
		printk("watt_wf:irq %d request failed!\r\n", device.irqnum);
		return -EFAULT;
	}
	//device.irq_pulse_handler=
	/* 一般情况下会注册对应的字符设备，但是这里我们使用MISC设备
	* 所以我们不需要自己注册字符设备驱动，只需要注册misc设备驱动即可
	*/
	ret = misc_register(&watt_hour_meter_miscdev);
	if (ret < 0) {
		printk("watt_wf:misc device register failed!\r\n");
		return -EFAULT;
	}
	/* 创建定时器 */
	init_timer(&device.timer);
	device.timer.function = timer_function;

	ret = sysfs_create_group(&dev->dev.kobj, &watt_hour_meter_sysfs_files);
	if (ret)
		return ret;
	return 0;
}

/*
* @description     : platform驱动的remove函数，移除platform驱动的时候此函数会执行
* @param - dev     : platform设备
* @return          : 0，成功;其他负值,失败
*/
static int device_remove(struct platform_device *dev)
{
	sysfs_remove_group(&dev->dev.kobj, &watt_hour_meter_sysfs_files);
	del_timer_sync(&device.timer);	/* 删除定时器 */
	/* 释放中断 */
	free_irq(device.irqnum, &device);
	gpio_free(device.pulsegpio);	
	/* 注销misc设备 */
	misc_deregister(&watt_hour_meter_miscdev);
	return 0;
}

/* 匹配列表 */
static const struct of_device_id device_of_match[] = {
	{ .compatible = "watt_hour_meter" },
	{ /* Sentinel */ }
};

/* platform驱动结构体 */
static struct platform_driver driver = {
	.driver = {
		.name = "watt_hour_meter",         /* 驱动名字，用于和设备匹配 */
		.of_match_table = device_of_match, /* 设备树匹配表          */
	},
	.probe = device_probe,
	.remove = device_remove,
};

/*
* @description	: 驱动出口函数
* @param 		: 无
* @return 		: 无
*/
static int __init watt_hour_meter_init(void)
{	
	InitPulseCount(device.pulseCount.buf);
	device.bCalcPower = 1;
	device.CalcPulseCount = 0;
	device.bFistCalcPulse = 1;
	tasklet_init(&tasklet_pulse, tasklet_pulse_func, (unsigned long)(&device));
	return platform_driver_register(&driver);
}

/*
* @description	: 驱动出口函数
* @param 		: 无
* @return 		: 无
*/
static void __exit watt_hour_meter_exit(void)
{
	platform_driver_unregister(&driver);
}

module_init(watt_hour_meter_init);
module_exit(watt_hour_meter_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("hrbeu wangf0228");
