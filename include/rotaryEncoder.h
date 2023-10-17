#include <pthread.h>
#include "Control.h"
#include "InputDevice.h"

class RotaryEncoder : public Control,public InputDevice{

public:
    RotaryEncoder(char* rotaryEvent); 

private:
    void processInput(input_event* ev);

};