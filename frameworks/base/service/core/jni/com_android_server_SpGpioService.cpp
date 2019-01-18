#define LOG_TAG "GPIOService"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"
#include "utils/misc.h"
#include "utils/Log.h"
#include "hardware/hardware.h"
#include "hardware/sp_gpio.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "assert.h"

#define LOGV(fmt,args...) ALOGV(fmt,##args)
#define LOGD(fmt,args...) ALOGD(fmt,##args)
#define LOGI(fmt,args...) ALOGI(fmt,##args)
#define LOGW(fmt,args...) ALOGW(fmt,##args)
#define LOGE(fmt,args...) ALOGE(fmt,##args)

struct onview_gpio_device_t *sSpLedDevice = NULL;
namespace android
{

    static void SpGpio_Ctrl_work(JNIEnv * env , jobject thiz,jint state)
    {
        LOGI("SpGpioService: Ctrl work led is open");
        if(sSpLedDevice == NULL)
        {
            LOGE("SpGpioService: SpLedDevice is not found");
            return;
        }else{
         sSpLedDevice->work_led_ctrl(sSpLedDevice,state);
         return;
        }
    }
    static void SpGpio_Ctrl_error(JNIEnv * env , jobject thiz,jint state)
    {
        LOGI("SpGpioService: Ctrl work led is open");
        if(sSpLedDevice == NULL)
        {
            LOGE("SpGpioService: SpLedDevice is not found");
            return;
        }else{
         sSpLedDevice->error_led_ctrl(sSpLedDevice,state);
         return;
        }
    }
    static void SpGpio_Ctrl_diy(JNIEnv * env , jobject thiz,jint state)
     {
         LOGI("SpGpioService: Ctrl work led is open");
         if(sSpLedDevice == NULL)
         {
             LOGE("SpGpioService: SpLedDevice is not found");
             return;
         }else{
          sSpLedDevice->diy_led_ctrl(sSpLedDevice,state);
          return;
         }
     }
    static inline int open_onview_gpio(const hw_module_t* module,struct onview_gpio_device_t** device){
        return module->methods->open(module,ONVIEW_GPIO_HARDWARE_DEVICE_ID,(struct hw_device_t** )device);
    }

    static jint GpService_init(JNIEnv* env,jclass clazz){
        onview_gpio_module_t* module;
        int ret = -1;
        LOGI("Initializing HAL stub OnViewGpio....");
        ret = hw_get_module(ONVIEW_GPIO_HARDWARE_MODULE_ID,(const struct hw_module_t **)&module);
        if(ret== 0)
        {
            LOGI("Device OnViewGpio found");
            if(open_onview_gpio(&module->common,&sSpLedDevice) == 0)
            {
                LOGI("Device OnViewGpio is open");
                return 1;
            }
            LOGE("Failed to open device OnViewGpio");
        }
        LOGE("Failed to Found device OnViewGpio ,ret = %d",ret);
        return 0;
    }

    static const JNINativeMethod method_table[]{
        {"init_native","()I",(void*)GpService_init},
        {"native_work_ctrl","(I)V",(void*)SpGpio_Ctrl_work},
        {"native_error_ctrl","(I)V",(void*)SpGpio_Ctrl_error},
        {"native_diy_ctrl","(I)V",(void*)SpGpio_Ctrl_diy},
    };

    int register_android_server_SpGpioService(JNIEnv* env)
    {
        jclass clazz = env->FindClass("com/android/server/SpGpioService");
        if (clazz == NULL) {
            ALOGE("Can't find com/android/server/SpGpioService");
            return -1;
        }
        return jniRegisterNativeMethods(env,"com/android/server/SpGpioService",method_table,NELEM(method_table));
    }
};