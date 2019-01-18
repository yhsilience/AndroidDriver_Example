#ifndef ANDROID_ONVIEW_GPIO_INTERFACE_H
#define ANDROID_ONVIEW_GPIO_INTERFACE_H

#include <hardware/hardware.h>
__BEGIN_DECLS

#define ONVIEW_GPIO_HARDWARE_MODULE_ID "OnViewGpio"

#define ONVIEW_GPIO_HARDWARE_DEVICE_ID "OnViewGpio"
struct onview_gpio_module_t{
    struct hw_module_t common;
};
struct onview_gpio_device_t {
    struct hw_device_t common;
    int fd;
    int (*work_led_ctrl)(struct onview_gpio_device_t *dev,int state);
    int (*error_led_ctrl)(struct onview_gpio_device_t *dev,int state);
    int (*diy_led_ctrl)(struct onview_gpio_device_t *dev,int state);
};
__END_DECLS
#endif