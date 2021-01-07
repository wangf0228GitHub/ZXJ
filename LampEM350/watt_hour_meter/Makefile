KERNELDIR := /home/wangf0228/work/bsp/linux-imx6ull-4.9.88
CURRENT_PATH := $(shell pwd)

obj-m := watt_hour_meter.o

build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean