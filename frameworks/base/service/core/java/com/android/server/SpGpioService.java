package com.android.server;

import android.content.Context;
import android.os.ISpGpioService;
import android.util.Slog;


public class  SpGpioService extends ISpGpioService.Stub {

    private  static  final  String TAG = "SpGpioService";

    private  int mPtr = 0;

    public SpGpioService(){
        mPtr = init_native();
        if(mPtr == 0){
            Slog.e(TAG,"Failed to initialize OnViewGpio Service.");
        }
    }
    public void WorkLed_ctrl(int state)
    {
        native_work_ctrl(state);
    }
    public void ErrorLed_ctrl(int state)
    {
        native_error_ctrl(state);
    }
    public void DiyLed_ctrl(int state)
    {
        native_diy_ctrl(state);
    }

    private  static  native  int    init_native();
    private  static  native  void   native_work_ctrl(int state);
    private  static  native  void   native_error_ctrl(int state);
    private  static  native  void   native_diy_ctrl(int state);
};