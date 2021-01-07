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
#define DEVICE_NAME		"watt_hour_meter"	/* ���� 	*/
#define DEVICE_MINOR	100			/* ���豸�� */


struct _powerlimit {
	unsigned int PowerUp;
	unsigned int PowerDown;
};

#define ioctlcmd_ResetPulseCount	(_IO('w', 0x1))	
#define ioctlcmd_ResetCalcPower		(_IO('w', 0x2))

#define CalcPulseMax 10
#define CalcConst (int)(9000*CalcPulseMax*1000)//1�ȵ�400�����,ÿ������9000J
/* watt_hour_meter�豸�ṹ�� */
typedef union {
	int count;
	unsigned char buf[4];
}_PulseCount;
struct watt_hour_meter_dev {
//	dev_t devid;			/* �豸�� 	 */
// 	struct cdev cdev;		/* cdev 	*/
// 	struct class *class;	/* �� 		*/
// 	struct device *device;	/* �豸 	 */
	struct device_node	*nd; /* �豸�ڵ� */
	int pulsegpio;			/* ������ʹ�õ�GPIO���		*/
	struct timer_list timer;/* ����һ����ʱ��*/
	int irqnum;				/* �жϺ�     */
	
	_PulseCount pulseCount;
	int bCalcPower;
	int bFistCalcPulse;
	int CalcPulseCount;
	unsigned long  start_jiffies;
	unsigned long  end_jiffies;
	int curPower;
	//struct _powerlimit powerlimit;
	struct fasync_struct *async_queue;		/* �첽��ؽṹ�� */
};

struct watt_hour_meter_dev device;		/* �豸 */
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
	filp = filp_open(MY_FILE, O_RDWR | O_CREAT, 0777); //�����ļ�
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
	filp = filp_open(MY_FILE, O_RDWR | O_CREAT, 0777); //�����ļ�
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
/* tasklet ������ */
void tasklet_pulse_func(unsigned long data)
{
	/* tasklet ���崦������ */
	unsigned int power_ms;
	struct watt_hour_meter_dev* pDevice = (struct watt_hour_meter_dev*)data;
	pDevice->pulseCount.count++;
	SavePulseCount(pDevice->pulseCount.buf);
	if(pDevice->bCalcPower)
	{
		if (pDevice->CalcPulseCount == CalcPulseMax)//������ɣ���ʼ����
		{
			power_ms = jiffies_to_msecs(pDevice->end_jiffies - pDevice->start_jiffies);
			pDevice->curPower = CalcConst / power_ms;
			printk("watt_wf:current power is %d ms -> %d w\n", power_ms, pDevice->curPower);
			pDevice->CalcPulseCount = 0;
			pDevice->bFistCalcPulse = 1;
			if (pDevice->async_queue)
				kill_fasync(&pDevice->async_queue, SIGIO, pDevice->curPower);	/* �ͷ�SIGIO�ź� */
		}
	}
	printk("watt_wf:pulse count is %d \n", pDevice->pulseCount.count);
}

/* @description		: �жϷ�������������ʱ������ʱ10ms��
*				  	  ��ʱ����������������
* @param - irq 	: �жϺ�
* @param - dev_id	: �豸�ṹ��
* @return 			: �ж�ִ�н��
*/
static irqreturn_t irqhandler_pulse(int irq, void *dev_id)
{
	struct watt_hour_meter_dev *dev = (struct watt_hour_meter_dev *)dev_id;
	dev->timer.data = (volatile long)dev_id;
	mod_timer(&dev->timer, jiffies + msecs_to_jiffies(10));	/* 10ms��ʱ */
	//printk("watt_wf:io irq\r\n");
	return IRQ_RETVAL(IRQ_HANDLED);
}
/* @description	: ��ʱ�������������ڰ�����������ʱ�������Ժ�
*				  �ٴζ�ȡ����ֵ������������Ǵ��ڰ���״̬�ͱ�ʾ������Ч��
* @param - arg	: �豸�ṹ����
* @return 		: ��
*/
void timer_function(unsigned long arg)
{
	unsigned char value;
	struct watt_hour_meter_dev *dev = (struct watt_hour_meter_dev *)arg;
	value = gpio_get_value(dev->pulsegpio); 	/* ��ȡIOֵ */
	if (value == 0)
	{
		if (dev->bCalcPower != 0)//��Ҫ���㹦��
		{
			if (dev->bFistCalcPulse != 0)//���㹦�ʵĵ�һ������
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
// 	struct watt_hour_meter_dev *dev = filp->private_data;
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
	struct watt_hour_meter_dev *dev = (struct watt_hour_meter_dev *)filp->private_data;
	switch (cmd) {
	case ioctlcmd_ResetPulseCount:		/* �رն�ʱ�� */
		dev->pulseCount.count=0;
		SavePulseCount(dev->pulseCount.buf);
		break;
	case ioctlcmd_ResetCalcPower:		/* �򿪶�ʱ�� */
		dev->bFistCalcPulse = 1;
		dev->CalcPulseCount = 0;
		break;
	default:
		break;
	}
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
	struct watt_hour_meter_dev *dev = (struct watt_hour_meter_dev *)filp->private_data;
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
	.read=device_read,
	.unlocked_ioctl= device_unlocked_ioctl,
	.fasync = device_fasync,
	.release = device_release
};

/* MISC�豸�ṹ�� */
static struct miscdevice watt_hour_meter_miscdev = {
	.minor = DEVICE_MINOR,
	.name = DEVICE_NAME,
	.fops = &device_fops,
};
/*
* @description     : flatform������probe��������������
*                    �豸ƥ���Ժ�˺����ͻ�ִ��
* @param - dev     : platform�豸
* @return          : 0���ɹ�;������ֵ,ʧ��
*/
static int device_probe(struct platform_device *dev)
{
	int ret = 0;
	printk("watt_wf:watt_hour_meter driver and device was matched!\r\n");
	/* ����watt_hour_meter��ʹ�õ�GPIO */
	/* 1����ȡ�豸�ڵ㣺watt_hour_meter */
	device.nd = of_find_node_by_path("/watt_hour_meter");
	if (device.nd == NULL) {
		printk("watt_wf:watt_hour_meter node not find!\r\n");
		return -EINVAL;
	}

	/* 2�� ��ȡ�豸���е�gpio����*/
	device.pulsegpio = of_get_named_gpio(device.nd, "pulsegpio", 0);
	if (device.pulsegpio < 0) {
		printk("watt_wf:can't get pulsegpio");
		return -EINVAL;
	}

	/* 3������GPIO5_IO01Ϊ�������������ߵ�ƽ��Ĭ�Ϲر�BEEP */
	ret=gpio_request(device.pulsegpio, "PowerPulse");	/* ����IO */
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
	/* һ������»�ע���Ӧ���ַ��豸��������������ʹ��MISC�豸
	* �������ǲ���Ҫ�Լ�ע���ַ��豸������ֻ��Ҫע��misc�豸��������
	*/
	ret = misc_register(&watt_hour_meter_miscdev);
	if (ret < 0) {
		printk("watt_wf:misc device register failed!\r\n");
		return -EFAULT;
	}
	/* ������ʱ�� */
	init_timer(&device.timer);
	device.timer.function = timer_function;

	ret = sysfs_create_group(&dev->dev.kobj, &watt_hour_meter_sysfs_files);
	if (ret)
		return ret;
	return 0;
}

/*
* @description     : platform������remove�������Ƴ�platform������ʱ��˺�����ִ��
* @param - dev     : platform�豸
* @return          : 0���ɹ�;������ֵ,ʧ��
*/
static int device_remove(struct platform_device *dev)
{
	sysfs_remove_group(&dev->dev.kobj, &watt_hour_meter_sysfs_files);
	del_timer_sync(&device.timer);	/* ɾ����ʱ�� */
	/* �ͷ��ж� */
	free_irq(device.irqnum, &device);
	gpio_free(device.pulsegpio);	
	/* ע��misc�豸 */
	misc_deregister(&watt_hour_meter_miscdev);
	return 0;
}

/* ƥ���б� */
static const struct of_device_id device_of_match[] = {
	{ .compatible = "watt_hour_meter" },
	{ /* Sentinel */ }
};

/* platform�����ṹ�� */
static struct platform_driver driver = {
	.driver = {
		.name = "watt_hour_meter",         /* �������֣����ں��豸ƥ�� */
		.of_match_table = device_of_match, /* �豸��ƥ���          */
	},
	.probe = device_probe,
	.remove = device_remove,
};

/*
* @description	: �������ں���
* @param 		: ��
* @return 		: ��
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
* @description	: �������ں���
* @param 		: ��
* @return 		: ��
*/
static void __exit watt_hour_meter_exit(void)
{
	platform_driver_unregister(&driver);
}

module_init(watt_hour_meter_init);
module_exit(watt_hour_meter_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("hrbeu wangf0228");
