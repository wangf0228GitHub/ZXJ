#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/bcd.h>
#include <linux/rtc.h>
#include <linux/mutex.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

//#define DEBUG
#include <linux/device.h>
//#undef DEBUG
#define DEVICE_NAME		"rtcSD250X"	/* 名字 	*/

static struct i2c_driver SD25xx_driver;
// SD-25xx Basic Time and Calendar Register definitions
#define SD25xx_SEC					0x00
#define SD25xx_MIN					0x01
#define SD25xx_HOUR				0x02
#define SD25xx_WEEK				0x03
#define SD25xx_DAY					0x04
#define SD25xx_MONTH				0x05
#define SD25xx_YEAR				0x06
#define SD25xx_ALARM_SEC			0x07
#define SD25xx_ALARM_MIN			0x08
#define SD25xx_ALARM_HOUR			0x09
#define SD25xx_ALARM_WEEK			0x0A
#define SD25xx_ALARM_DAY			0x0B
#define SD25xx_ALARM_MONTH		0x0C
#define SD25xx_ALARM_YEAR			0x0D

#define SD25xx_ALARM_EN			0x0E
#       define SD25XX_ALARM_EAY	(1 << 6)
#       define SD25xx_ALARM_EAMO	(1 << 5)
#       define SD25xx_ALARM_EAD	(1 << 4)
#       define SD25xx_ALARM_EAW	(1 << 3)
#       define SD25xx_ALARM_EAH	(1 << 2)
#       define SD25xx_ALARM_EAMN	(1 << 1)
#       define SD25xx_ALARM_EAS	(1 << 0)

#define SD25xx_CTR1				0x0F	/* Control register 1 */
#       define SD25xx_CTR1_WRTC3	(1 << 7)
#       define SD25xx_CTR1_INTAF	(1 << 5)
#       define SD25xx_CTR1_INTDF	(1 << 4)
#       define SD25xx_CTR1_WRTC2	(1 << 2)
#       define SD25xx_CTR1_RTCF	(1 << 0)

#define SD25xx_CTR2				0x10
#       define SD25xx_CTR2_WRTC1	(1 << 7)
#       define SD25xx_CTR2_IM		(1 << 6)
#       define SD25xx_CTR2_INTS1	(1 << 5)
#       define SD25xx_CTR2_INTS0	(1 << 4)
#       define SD25xx_CTR2_FOBAT	(1 << 3)
#       define SD25xx_CTR2_INTDE	(1 << 2)
#       define SD25xx_CTR2_INTAE	(1 << 1)
#       define SD25xx_CTR2_INTFE	(1 << 0)

#define SD25xx_CTR3				0x11
#       define SD25xx_CTR3_ARST	(1 << 7)
#       define SD25xx_CTR3_TDS1	(1 << 5)
#       define SD25xx_CTR3_TDS0	(1 << 4)
#       define SD25xx_CTR3_FS3		(1 << 3)
#       define SD25xx_CTR3_FS2		(1 << 2)
#       define SD25xx_CTR3_FS1		(1 << 1)
#       define SD25xx_CTR3_FS0		(1 << 0)

#define SD25xx_CTR5				0x1A
#       define SD25xx_CTR5_BAT8_VAL	(1 << 7)

#define SD25xx_BAT_VAL				0x1B
#       define SD25xx_CTR5_BAT7_VAL	(1 << 7)
#       define SD25xx_CTR5_BAT6_VAL	(1 << 6)
#       define SD25xx_CTR5_BAT5_VAL	(1 << 5)
#       define SD25xx_CTR5_BAT4_VAL	(1 << 4)
#       define SD25xx_CTR5_BAT3_VAL	(1 << 3)
#       define SD25xx_CTR5_BAT2_VAL	(1 << 2)
#       define SD25xx_CTR5_BAT1_VAL	(1 << 1)
#       define SD25xx_CTR5_BAT0_VAL	(1 << 0)

#define	SD25xx_ID_1st				0x72


#define READ_RTC_INFO 0

//----------------------------------------------------------------------
// SD25xx_read_reg()
// reads a SD25xx register (see Register defines)
// See also SD25xx_read_regs() to read multiple registers.
//
//----------------------------------------------------------------------
static int SD25xx_read_reg(struct i2c_client *client, unsigned char addr)
{
	return 0x55;
// 	int ret = i2c_smbus_read_byte_data(client, addr);
// 
// 	//check for error
// 	if (ret < 0) {
// 		dev_err(&client->dev, "Unable to read register #%d\n", addr);
// 	}
// 
// 	return ret;
}

//----------------------------------------------------------------------
// SD25xx_read_regs()
// reads a specified number of SD25xx registers (see Register defines)
// See also SD25xx_read_reg() to read single register.
//----------------------------------------------------------------------
static int SD25xx_read_regs(struct i2c_client *client, unsigned char addr, unsigned char *pBuf, unsigned char len)
{
	while (len--)
	{
		*pBuf = len;
		pBuf++;
	}
	return len;
//  	int ret = i2c_smbus_read_i2c_block_data(client, addr,len, pBuf);
//  
//  	//check for length error
//  	if (ret == -1) 
// 	{
//  		dev_err(&client->dev, "Unable to read \n");
//  		return ret < 0 ? ret : -EIO;
//  	} 
//  	return 0;
}

static int i2c_write_byte(struct i2c_client *client, u8 addr, u8 value)
{
	return 0;
// 	int ret = i2c_smbus_write_byte_data(client, addr, value);
// 
// 	//check for error
// 	if (ret)
// 		dev_err(&client->dev, "Unable to write register #%d\n", addr);
// 
// 	return ret;
}
//----------------------------------------------------------------------
// SD25xx_write_enable()
// sets SD25xx write enable
//----------------------------------------------------------------------
static void SD25xx_write_enable(struct i2c_client *client)
{
	int ret;

	ret = SD25xx_read_reg(client, SD25xx_CTR2);
	ret = ret | SD25xx_CTR2_WRTC1;
	i2c_write_byte(client, SD25xx_CTR2, ret);

	ret = SD25xx_read_reg(client, SD25xx_CTR1);
	ret = ret | SD25xx_CTR1_WRTC3 | SD25xx_CTR1_WRTC2;
	i2c_write_byte(client, SD25xx_CTR1, ret);
}

//----------------------------------------------------------------------
// SD25xx_write_disable()
// sets SD25xx write disable
//----------------------------------------------------------------------
static void SD25xx_write_disable(struct i2c_client *client)
{
	char ret;

	ret = SD25xx_read_reg(client, SD25xx_CTR1);
	ret = ret & (~SD25xx_CTR1_WRTC3) & (~SD25xx_CTR1_WRTC2);
	i2c_write_byte(client, SD25xx_CTR1, ret);

	ret = SD25xx_read_reg(client, SD25xx_CTR2);
	ret = ret & (~SD25xx_CTR2_WRTC1);
	i2c_write_byte(client, SD25xx_CTR2, ret);
}

//----------------------------------------------------------------------
// SD25xx_write_regs()
// writes a specified number of SD25xx registers (see Register defines)
// See also SD25xx_write_reg() to write a single register.
//
//----------------------------------------------------------------------
static int SD25xx_write_regs(struct i2c_client *client, unsigned char addr, unsigned char *values, unsigned char length)
{
	return 0;
// 	int ret;
// 	SD25xx_write_enable(client);
// 	ret = i2c_smbus_write_i2c_block_data(client, addr, length, values);
// 	//check for error
// 	if (ret)
// 		dev_err(&client->dev, "Unable to write registers #%d..#%d\n", addr, addr + length - 1);
// 	SD25xx_write_disable(client);
// 	return ret;
}
/************************************************************************/
/* sysfs                                                                */
/************************************************************************/
static ssize_t SD25xx_sysfs_show_temperature(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	u8 regs[1] = { 0, };
	int err;
	err = SD25xx_read_regs(client, 0x16, regs, 1);
	if (err)
	{
		dev_err(&client->dev, "%s: reading temperature section failed\n",
			__func__);
		return err;
	}

	return sprintf(buf, "%d", regs[0]);
}

static DEVICE_ATTR(temperature, S_IRUGO, SD25xx_sysfs_show_temperature, NULL);

static ssize_t SD25xx_sysfs_show_VBat(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	u8 regs[2] = { 0, };
	int err;
	int Vbat_val;
	err = SD25xx_read_regs(client, 0x1b, regs, 2);
	if (err)
	{
		dev_err(&client->dev, "%s: reading VBat section failed\n",
			__func__);
		return err;
	}
	Vbat_val = (regs[0] >> 7) * 256 + regs[1];
	return sprintf(buf, "%d.%d%dV\n", Vbat_val / 100, (Vbat_val % 100) / 10, Vbat_val % 10);
}

static DEVICE_ATTR(VBat, S_IRUGO, SD25xx_sysfs_show_VBat, NULL);

static struct attribute *SD25xx_attrs[] = {
	&dev_attr_temperature.attr,
	&dev_attr_VBat.attr,
	NULL
};

static const struct attribute_group SD25xx_sysfs_files = {
	.attrs = SD25xx_attrs,
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
static int SD25xx_proc(struct device *dev, struct seq_file *seq)
{
	struct i2c_client *const client = to_i2c_client(dev);
	unsigned char regs[7];
	int err;
	int Vbat_val;
	err = SD25xx_read_regs(client, SD25xx_ALARM_EN, regs, 5);
	if (err)
	{
		dev_err(&client->dev, "%s: reading section failed\n",
			__func__);
		return err;
	}
	seq_printf(seq, "ALARM_EN\t:%02x\n", regs[0]);
	seq_printf(seq, "CTR1\t:%02x\n", regs[1]);
	seq_printf(seq, "CTR2\t:%02x\n", regs[2]);
	seq_printf(seq, "CTR3\t:%02x\n", regs[3]);
	seq_printf(seq, "TTF\t:%02x\n", regs[4]);

	err = SD25xx_read_regs(client, 0x16, regs, 6);
	if (err)
	{
		dev_err(&client->dev, "%s: reading section failed\n",
			__func__);
		return err;
	}
	seq_printf(seq, "Temperature\t:%02x\n", regs[0]);
	seq_printf(seq, "AGTC\t:%02x\n", regs[1]);
	seq_printf(seq, "CHARGE\t:%02x\n", regs[2]);
	seq_printf(seq, "CTR4\t:%02x\n", regs[3]);
	seq_printf(seq, "CTR5\t:%02x\n", regs[4]);
	Vbat_val = (regs[4] >> 7) * 256 + regs[1];
	seq_printf(seq, "BAT_VAL\t:%d.%d%dV\n", Vbat_val / 100, (Vbat_val % 100) / 10, Vbat_val % 10);
	return 0;
}
static int SD25xx_read_time(struct device *dev, struct rtc_time *dt)
{
	struct i2c_client *client = to_i2c_client(dev);
	unsigned char date[7];
	int err;	 
	err = SD25xx_read_regs(client, SD25xx_SEC, date,7);
	if (err)
	{
		dev_err(&client->dev, "%s: reading section failed\n",
			__func__);
		return err;
	}
	 
	dev_dbg(&client->dev, "%s: read 0x%02x 0x%02x "
	 	"0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n", __func__,
	 	date[0], date[1], date[2], date[3], date[4], date[5], date[6]);
	 
	dt->tm_sec = bcd2bin(date[SD25xx_SEC] & 0x7f);
	dt->tm_min = bcd2bin(date[SD25xx_MIN] & 0x7f);

	/* HR field has a more complex interpretation */
	{
		const u8 _hr = date[SD25xx_HOUR];
		if (_hr & 0x80)	/* 24h format */
			dt->tm_hour = bcd2bin(_hr & 0x3f);
		else {
			/* 12h format */
			dt->tm_hour = bcd2bin(_hr & 0x1f);
			if (_hr & 0x20)	/* PM flag set */
				dt->tm_hour += 12;
		}
	}
	//dt->tm_hour = bcd2bin(date[SD25xx_HOUR] & 0x3f);//24h format
	dt->tm_wday = bcd2bin(date[SD25xx_WEEK] & 0x07);
	dt->tm_mday = bcd2bin(date[SD25xx_DAY] & 0x3f);
	dt->tm_mon = bcd2bin(date[SD25xx_MONTH] & 0x1f);
	dt->tm_year = bcd2bin(date[SD25xx_YEAR]);
	 
	//if (dt->tm_year < 70)
	dt->tm_year += 100;
	 
	dev_info(&client->dev, "%s: date %d:%d:%d  %d-%d-%d  weekday:%d\n", __func__,
	 	dt->tm_hour, dt->tm_min, dt->tm_sec, dt->tm_year + 1900, dt->tm_mon,
	 	dt->tm_mday, dt->tm_wday);

	return rtc_valid_tm(dt);
}
static int SD25xx_set_time(struct device *dev, struct rtc_time *dt)
{
	struct i2c_client *client = to_i2c_client(dev);
	unsigned char date[7];
	int ret = 0;

	date[SD25xx_SEC] = bin2bcd(dt->tm_sec);
	date[SD25xx_MIN] = bin2bcd(dt->tm_min);
	date[SD25xx_HOUR] = bin2bcd(dt->tm_hour) | 0x80;
	date[SD25xx_WEEK] = bin2bcd(dt->tm_wday);
	date[SD25xx_DAY] = bin2bcd(dt->tm_mday);
	date[SD25xx_MONTH] = bin2bcd(dt->tm_mon);
	date[SD25xx_YEAR] = bin2bcd(dt->tm_year % 100);

	dev_dbg(&client->dev, "%s: write 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
		__func__, date[0], date[1], date[2], date[3], date[4], date[5], date[6]);

	ret = SD25xx_write_regs(client, SD25xx_SEC,date,7);

	return 0;// ret;
}
static int SD25xx_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct rtc_time *const tm = &alarm->time;
	u8 regs[10] = { 0, };
	int err;
	err = SD25xx_read_regs(client, SD25xx_ALARM_SEC, regs, 10);
	if (err)
	{
		dev_err(&client->dev, "%s: reading alarm section failed\n",
			__func__);
		return err;
	}
	tm->tm_sec = bcd2bin(regs[0] & 0x7f);
	tm->tm_min = bcd2bin(regs[1] & 0x7f);
	tm->tm_hour = bcd2bin(regs[2] & 0x3f);
	tm->tm_mday = bcd2bin(regs[4] & 0x3f);
	tm->tm_mon = bcd2bin(regs[5] & 0x1f);
	tm->tm_wday = bcd2bin(regs[3]);
	tm->tm_year = bcd2bin(regs[6])+100;
	alarm->pending = !!(regs[8] & SD25xx_CTR1_INTAF);
	alarm->enabled = !!(regs[9] & SD25xx_CTR2_INTAE);
	return 0;
}
static int SD25xx_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct i2c_client *client = to_i2c_client(dev);
	unsigned char date[8],ctr2;
	int ret = 0;
	struct rtc_time *alarm_tm = &alarm->time;
	memset(date, 0, 8);
	//date[7] = 0;
	if (alarm_tm->tm_sec & 0x80)
	{
		date[0] = bin2bcd(alarm_tm->tm_sec&0x80);
		date[7] |= 0x01;
	}
	if (alarm_tm->tm_min & 0x80)
	{
		date[1] = bin2bcd(alarm_tm->tm_min & 0x80);
		date[7] |= 0x02;
	}
	if (alarm_tm->tm_hour & 0x80)
	{
		date[2] = bin2bcd(alarm_tm->tm_hour & 0x80);
		date[7] |= 0x04;
	}
	if (alarm_tm->tm_wday & 0x80)
	{
		date[3] = bin2bcd(alarm_tm->tm_wday & 0x80);
		date[7] |= 0x08;
	}
	if (alarm_tm->tm_mday & 0x80)
	{
		date[4] = bin2bcd(alarm_tm->tm_mday & 0x80);
		date[7] |= 0x10;
	}
	if (alarm_tm->tm_mon & 0x80)
	{
		date[5] = bin2bcd(alarm_tm->tm_mon & 0x80);
		date[7] |= 0x20;
	}
	if (alarm_tm->tm_year & 0x80)
	{
		date[6] = bin2bcd((alarm_tm->tm_year & 0x80)%100);
		date[7] |= 0x40;
	}
	dev_dbg(&client->dev, "%s: write 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
		__func__, date[0], date[1], date[2], date[3], date[4], date[5], date[6], date[7]);

	ret = SD25xx_write_regs(client, SD25xx_ALARM_SEC,date,8);
	if (ret)
	{
		dev_err(&client->dev, "%s: setting alarm section failed\n",
			__func__);
		return ret;
	}
	if(alarm->enabled)
	{
		ctr2 = SD25xx_CTR2_WRTC1 | SD25xx_CTR2_INTS0 | SD25xx_CTR2_INTAE;		
	}
	else
	{
		ctr2 = SD25xx_CTR2_WRTC1 | SD25xx_CTR2_INTS0;
	}
	ret = SD25xx_write_regs(client, SD25xx_CTR2, &ctr2,1);
	if (ret)
	{
		dev_err(&client->dev, "%s: setting alarm enabled failed\n",
			__func__);
		return ret;
	}
	return 0;
}
static const struct rtc_class_ops rtcSD25xx_ops = {
 	.proc = SD25xx_proc,
 	.read_time = SD25xx_read_time,
 	.set_time = SD25xx_set_time,
 	.read_alarm = SD25xx_read_alarm,
 	.set_alarm = SD25xx_set_alarm,
};
/*
* @description     : flatform驱动的probe函数，当驱动与
*                    设备匹配以后此函数就会执行
* @param - dev     : platform设备
* @return          : 0，成功;其他负值,失败
*/
static int device_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	//int ret = 0;	
	int rc = 0;
	unsigned char buf;
	struct rtc_device *rtc;
	dev_info(&client->dev,"rtc_wf:rtc SD250X driver and device was matched!\r\n");
	dev_info(&client->dev, "rtc_wf:client name : %s,%ld\r\n", client->name, id->driver_data);
// 	if (client->irq > 0) {
// 		rc = devm_request_threaded_irq(&client->dev, client->irq, NULL,
// 			isl1208_rtc_interrupt,
// 			IRQF_SHARED | IRQF_ONESHOT,
// 			isl1208_driver.driver.name,
// 			client);
// 		if (!rc) {
// 			device_init_wakeup(&client->dev, 1);
// 			enable_irq_wake(client->irq);
// 		}
// 		else {
// 			dev_err(&client->dev,
// 				"Unable to request irq %d, no alarm support\n",
// 				client->irq);
// 			client->irq = 0;
// 		}
// 	}

	rtc = devm_rtc_device_register(&client->dev, 
									SD25xx_driver.driver.name,
									&rtcSD25xx_ops,
									THIS_MODULE);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);
	rtc->uie_unsupported = 1;

	i2c_set_clientdata(client, rtc);

	rc = SD25xx_read_reg(client, SD25xx_CTR1);
	if (rc < 0) {
		dev_err(&client->dev, "reading status failed\n");
		return rc;
	}

	if (rc & SD25xx_CTR1_RTCF)
		dev_warn(&client->dev, "rtc power failure detected, "
			"please set clock.\n");
	buf = 0x82;
	rc = SD25xx_write_regs(client, 0x18,&buf,1);
	if (rc < 0) {
		dev_err(&client->dev, "write status failed\n");
		return rc;
	}

	rc = sysfs_create_group(&client->dev.kobj, &SD25xx_sysfs_files);
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
	sysfs_remove_group(&client->dev.kobj, &SD25xx_sysfs_files);
	return 0;
}
/* 传统匹配方式ID列表 */
static const struct i2c_device_id device_id[] = {
	{ "SD25xX", 101 },
	{ "SD250X", 100 },
	{}
};
//i2c client name 将是BH1750
//经测试，应为“，”后面的，即器件型号
/* 匹配列表 */
static const struct of_device_id device_of_match[] = {
	{.compatible = "WAVE,SD250X" },
	{ /* Sentinel */ }
};
static struct i2c_driver SD25xx_driver = {
	.driver = {
		.name = "rtc_SD250X",         /* 驱动名字，用于和设备匹配 */
		.of_match_table = device_of_match, /* 设备树匹配表          */
	},
	.probe = device_probe,
	.remove = device_remove,
	.id_table = device_id,
};

static int __init SD25xx_init(void)
{
	printk("rtc_wf:1111111111111!\r\n");
	return i2c_add_driver(&SD25xx_driver);
}

static void __exit SD25xx_exit(void)
{
	i2c_del_driver(&SD25xx_driver);
}

module_init(SD25xx_init);
module_exit(SD25xx_exit);
//module_i2c_driver(SD25xx_driver);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("hrbeu wangf0228");

