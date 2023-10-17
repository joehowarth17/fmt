#ifndef INPUT_DEVICE_H_
#define INPUT_DEVICE_H_

#include <pthread.h>
#include <linux/input.h>

class InputDevice{

public:

    InputDevice(char * path);
    int Init();
    int start();
    int stop();
    void printDeviceInfo();

protected:

    void monitorThread();
    virtual void processInput(input_event* ev);
    static void* _startMonitor(void *param);
    static constexpr int MAX_DEV_LEN = 128;
    char devicePath[MAX_DEV_LEN];
    int fd;
    bool running;
    

    pthread_t thread;

};

#endif