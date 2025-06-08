#include <pthread.h>
#include "Control.h"
#include "InputDevice.h"

class RotaryEncoder : public Control{

public:
    RotaryEncoder(std::string name):Control(name) {}; 
    ~RotaryEncoder(){};

protected:
    virtual void processInput(void* ev){};


};