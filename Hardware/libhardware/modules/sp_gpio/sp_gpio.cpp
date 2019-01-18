#define LOG_TAG "Sp_GpioHALStub"

#include <hardware/hardware.h>
#include <hardware/sp_gpio.h>

#include <fcntl.h>
//#include <ioctl.h>
#include <errno.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <cutils/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <memory.h>

#define LOGV(fmt,args...) ALOGV(fmt,##args)
#define LOGD(fmt,args...) ALOGD(fmt,##args)
#define LOGI(fmt,args...) ALOGI(fmt,##args)
#define LOGW(fmt,args...) ALOGW(fmt,##args)
#define LOGE(fmt,args...) ALOGE(fmt,##args)

#define DEVICE_NAME "/dev/onview-gpio"
#define MODULE_NAME "onview-gpio"
#define MODULE_AUTHOR "Yhsilience"

#define CMD_MAGIC  'a'
#define CMD_WORK_LED                  _IOW(CMD_MAGIC,0x01,char)
#define CMD_ERROR_LED                  _IOW(CMD_MAGIC,0x02,char)
#define CMD_DIY_LED                  _IOW(CMD_MAGIC,0x03,char)


static int work_led_ctrl(struct onview_gpio_device_t *dev,int state)
{
    int ret;
    char val;
    if(!dev)
    {
        LOGE("NULL dev pointer.");
        return -EFAULT;
    }
    LOGI("set the gpio state");
    if(state == 1)
        val = 1;
    else
        val = 0;
    ret = ioctl(dev->fd,CMD_WORK_LED,&val);
    if(ret < 0)
    {
        LOGE("set work led is Failed.");
        return -EFAULT;
    }
    return 0;
}
static int error_led_ctrl(struct onview_gpio_device_t *dev,int state)
{
    int ret;
    char val;
    if(!dev)
    {
        LOGE("NULL dev pointer.");
        return -EFAULT;
    }
    LOGI("set the gpio state");
    if(state == 1)
        val = 1;
    else
        val = 0;
    ret = ioctl(dev->fd,CMD_ERROR_LED,&val);
    if(ret < 0)
    {
        LOGE("set work led is Failed.");
        return -EFAULT;
    }
    return 0;
}
static int diy_led_ctrl(struct onview_gpio_device_t *dev,int state)
{
    int ret;
    char val;
    if(!dev)
    {
        LOGE("NULL dev pointer.");
        return -EFAULT;
    }
    LOGI("set the gpio state");
    if(state == 1)
        val = 1;
    else
        val = 0;
    ret = ioctl(dev->fd,CMD_DIY_LED,&val);
    if(ret < 0)
    {
        LOGE("set work led is Failed.");
        return -EFAULT;
    }
    return 0;
}
static int onview_gpio_device_close(struct hw_device_t* device)
{
	struct onview_gpio_device_t * dev = (struct onview_gpio_device_t *)device;
	if(dev)
	{
		close(dev->fd);
		free(dev);
	}
  return 0;
}

static int open_onview_gpio(const struct hw_module_t* module, char const* name,struct hw_device_t** device)
{
   	struct onview_gpio_device_t* dev;
   	dev = (struct onview_gpio_device_t *)malloc(sizeof(struct onview_gpio_device_t));
   	if(!dev)
   	{
   		LOGE("Failed to alloc space for onview_gpio_device_t\n");
   		return -EFAULT;
   	}
   	memset(dev,0,sizeof(struct onview_gpio_device_t));

   	dev->common.tag = HARDWARE_MODULE_TAG;
   	dev->common.version = 0;
   	dev->common.module = (hw_module_t *)module;
   	dev->common.close = onview_gpio_device_close;

    dev->work_led_ctrl = work_led_ctrl;
    dev->error_led_ctrl = error_led_ctrl;
    dev->diy_led_ctrl = diy_led_ctrl;
    *device = &(dev->common);

   dev->fd = open(DEVICE_NAME,O_RDWR);
   if(dev->fd == -1)
   {
   		LOGE("Failed open /dev/onview-gpio");
   		free(dev);
   		return -EFAULT;
   }
   return 0;
}

static struct hw_module_methods_t onview_gpio_module_methods =
{
   .open = open_onview_gpio
};

struct onview_gpio_module_t HAL_MODULE_INFO_SYM =
{
    .common = {
        .tag =HARDWARE_MODULE_TAG,
        .version_major =1,
        .version_minor = 0,
        .id = ONVIEW_GPIO_HARDWARE_MODULE_ID,
        .name = MODULE_NAME,
        .author = MODULE_AUTHOR,
        .methods = &onview_gpio_module_methods,
    }

};