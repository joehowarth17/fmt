#ifndef BUTTON_H_
#define BUTTON_H_

#include "Control.h"
#include "InputDevice.h"
#ifdef LINUX
class PushButton : public Control, public InputDevice{

public:

 PushButton(std::string name, char*  buttonEvent, int keycode);


private:

    int key;
    std::string label;
    void processInput(input_event* ev);

};

#endif
#endif