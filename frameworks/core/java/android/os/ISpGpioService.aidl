package android.os;

interface ISpGpioService{
    void WorkLed_ctrl(int state);
    void DiyLed_ctrl(int state);
    void ErrorLed_ctrl(int state);
}