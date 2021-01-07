KERNELDIR := /home/wangf0228/work/bsp/linux-imx6ull-4.9.88
CURRENT_PATH := $(shell pwd)

obj-m := LightSensor_BH1750.o
LightSensor_BH1750-y +=lightBH1750.o

build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean