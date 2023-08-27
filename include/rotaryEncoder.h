#include <pthread.h>
#include <Control.h>
class RotaryEncoder : public Control{

public:
    RotaryEncoder(char* rotaryEvent);


    int Init();
    //Returns angle between 0 360;
    int getAngle();
    int start();
    int stop();
    void printDeviceInfo();
    

private:

    void monitorThread();
    static void* _startMonitor(void *param);
    static constexpr int MAX_DEV_LEN = 128;
    char devicePath[MAX_DEV_LEN];
    int fd;
    bool running;
    

    pthread_t rotaryThread;


};