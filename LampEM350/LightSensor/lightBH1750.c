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

#define DEVICE_NAME		"lightBH1750"	/* ���� 	*/

#define LIGHTLISTMAX 16

/* light_sensor�豸�ṹ�� */

struct light_sensor_dev {
	dev_t devid;			/* �豸�� 	 */
	struct cdev cdev;		/* cdev 	*/
	struct class *class;	/* �� 		*/
	struct device *device;	/* �豸 	 */
	int major;			/* ���豸�� */
	struct timer_list timer;/* ����һ����ʱ��*/

	void *pI2C_clinet;	/* i2c client */
	int errTimes;
	int lightList[LIGHTLISTMAX];
	int lightListIndex;
	int bFullList;
	int curLight;
	//struct _powerlimit powerlimit;
	struct fasync_struct *async_queue;		/* �첽��ؽṹ�� */
};

struct light_sensor_dev device;		/* �豸 */

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

/* @description	: ��ʱ�������������ڰ�����������ʱ�������Ժ�
*				  �ٴζ�ȡ����ֵ������������Ǵ��ڰ���״̬�ͱ�ʾ������Ч��
* @param - arg	: �豸�ṹ����
* @return 		: ��
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
	mod_timer(&dev->timer, jiffies + msecs_to_jiffies(1000));	/* 1s��ʱ */
	while(retry!=0)
	{
		//0x20,1 lx �ֱ��ʣ�120ms����ʱ�䣬�������Զ�power down
		ret = i2c_master_send(dev->pI2C_clinet, cmd, 1);
		if (ret < 0) 
		{
			retry--;
			continue;
		}
		mdelay(150);
		ret = i2c_master_recv(dev->pI2C_clinet, (char *)&light, 2);              //���������ֽ����ݣ��Ƚ��ո߰�λ������յͰ�λ
		if (ret < 0) 
		{
			retry--;
			continue;
		}
		break;
	}
	if (retry != 0)//�ɹ���ȡ
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
				kill_fasync(&dev->async_queue, SIGIO, POLL_IN);	/* �ͷ�SIGIO�ź� */
		}
		else
		{
			if (dev->lightListIndex == LIGHTLISTMAX-1)
			{
				dev->bFullList = 1;
			}
		}	
	}
	else//��ȡʧ��
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
* @description		: ���豸
* @param - inode 	: ���ݸ�������inode
* @param - filp 	: �豸�ļ���file�ṹ���и�����private_data�ĳ�Ա����
* 					  һ����open��ʱ��private_dataָ���豸�ṹ�塣
* @return 			: 0 �ɹ�;���� ʧ��
*/
static int device_open(struct inode *inode, struct file *filp)
{
	filp->private_data = &device; /* ����˽������ */
	return 0;
}

/*
* @description     : ���豸��ȡ����
* @param - filp    : Ҫ�򿪵��豸�ļ�(�ļ�������)
* @param - buf     : ���ظ��û��ռ�����ݻ�����
* @param - cnt     : Ҫ��ȡ�����ݳ���
* @param - offt    : ������ļ��׵�ַ��ƫ��
* @return          : ��ȡ���ֽ��������Ϊ��ֵ����ʾ��ȡʧ��
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
* @description		: ���豸д����
* @param - filp 	: �豸�ļ�����ʾ�򿪵��ļ�������
* @param - buf 	: Ҫд���豸д�������
* @param - cnt 	: Ҫд������ݳ���
* @param - offt 	: ������ļ��׵�ַ��ƫ��
* @return 			: д����ֽ��������Ϊ��ֵ����ʾд��ʧ��
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
	// 	beepstat = databuf[0];		/* ��ȡ״ֵ̬ */
	// 	if (beepstat == BEEPON) {
	// 		gpio_set_value(dev->pulsegpio, 0);	/* �򿪷����� */
	// 	}
	// 	else if (beepstat == BEEPOFF) {
	// 		gpio_set_value(dev->pulsegpio, 1);	/* �رշ����� */
	// 	}
	return 0;
}
/*
* @description		: ioctl������
* @param - filp 	: Ҫ�򿪵��豸�ļ�(�ļ�������)
* @param - cmd 	: Ӧ�ó����͹���������
* @param - arg 	: ����
* @return 			: 0 �ɹ�;���� ʧ��
*/
static long device_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	//struct light_sensor_dev *dev = (struct light_sensor_dev *)filp->private_data;
	//switch (cmd) {
 //	case ioctlcmd_ResetPulseCount:		/* �رն�ʱ�� */
 //		dev->pulseCount.count = 0;
 //		SavePulseCount(dev->pulseCount.buf);
 //		break;
 //	case ioctlcmd_ResetCalcPower:		/* �򿪶�ʱ�� */
 //		dev->bFistCalcPulse = 1;
 //		dev->CalcPulseCount = 0;
 //		break;
	//default:
	//	break;
	//}
	return 0;
}

/*
* @description     : fasync���������ڴ����첽֪ͨ
* @param - fd		: �ļ�������
* @param - filp    : Ҫ�򿪵��豸�ļ�(�ļ�������)
* @param - on      : ģʽ
* @return          : ������ʾ����ִ��ʧ��
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
/* �豸�������� */
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
* @description     : flatform������probe��������������
*                    �豸ƥ���Ժ�˺����ͻ�ִ��
* @param - dev     : platform�豸
* @return          : 0���ɹ�;������ֵ,ʧ��
*/
static int device_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int rc = 0;

	printk("light_wf:light_sensor driver and device was matched!\r\n");
	printk("light_wf:client name : %s,%ld\r\n",client->name,id->driver_data);
	/* 1�������豸�� */
	alloc_chrdev_region(&device.devid, 0, 1, DEVICE_NAME);
	device.major = MAJOR(device.devid);
	/* 2��ע���豸 */
	cdev_init(&device.cdev, &device_fops);
	cdev_add(&device.cdev, device.devid, 1);

	/* 3�������� */
	device.class = class_create(THIS_MODULE, DEVICE_NAME);
	if (IS_ERR(device.class)) {
		return PTR_ERR(device.class);
	}
	/* 4�������豸 */
	device.device = device_create(device.class, NULL, device.devid, NULL, DEVICE_NAME);
	if (IS_ERR(device.device)) {
		return PTR_ERR(device.device);
	}

	device.pI2C_clinet = client;
	/* ������ʱ�� */
	init_timer(&device.timer);
	device.timer.function = timer_function;
	rc = sysfs_create_group(&client->dev.kobj, &lightBH1750_sysfs_files);
	if (rc)
		return rc;
	return 0;
}

/*
* @description     : platform������remove�������Ƴ�platform������ʱ��˺�����ִ��
* @param - dev     : platform�豸
* @return          : 0���ɹ�;������ֵ,ʧ��
*/
static int device_remove(struct i2c_client *client)
{
	sysfs_remove_group(&client->dev.kobj, &lightBH1750_sysfs_files);
	del_timer_sync(&device.timer);	/* ɾ����ʱ�� */
									/* �ͷ��ж� */
									/* ɾ���豸 */
	cdev_del(&device.cdev);
	unregister_chrdev_region(device.devid, 1);
	/* ע��������豸 */
	device_destroy(device.class, device.devid);
	class_destroy(device.class);
	return 0;
}
/* ��ͳƥ�䷽ʽID�б� */
static const struct i2c_device_id device_id[] = {
	{ "BH1750", 100 },
	{}
};
//i2c client name ����BH1750
//�����ԣ�ӦΪ����������ģ��������ͺ�
/* ƥ���б� */
static const struct of_device_id device_of_match[] = {
	{ .compatible = "ROHM,BH1750" },
	{ /* Sentinel */ }
};

/* platform�����ṹ�� */
static struct i2c_driver driver = {
	.driver = {
		.owner = THIS_MODULE,
		.name = "light_sensor_BH1750",         /* �������֣����ں��豸ƥ�� */
		.of_match_table = device_of_match, /* �豸��ƥ���          */
		},
	.probe = device_probe,
	.remove = device_remove,
	.id_table = device_id,
};

/*
* @description	: �������ں���
* @param 		: ��
* @return 		: ��
*/
static int __init light_sensor_init(void)
{
	device.errTimes = 0;
	device.lightListIndex = 0;
	device.curLight = 0;
	device.bFullList = 0;
	/* ������ʱ�� */
	init_timer(&device.timer);
	device.timer.function = timer_function;
	device.timer.data = (unsigned long)&device;
	mod_timer(&device.timer, jiffies + msecs_to_jiffies(1000));	/* 1s��ʱ */
	return i2c_add_driver(&driver);
}

/*
* @description	: �������ں���
* @param 		: ��
* @return 		: ��
*/
static void __exit light_sensor_exit(void)
{
	i2c_del_driver(&driver);
}

module_init(light_sensor_init);
module_exit(light_sensor_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("hrbeu wangf0228");
