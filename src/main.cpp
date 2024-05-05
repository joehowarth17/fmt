// Handles IO control for audio effects.
#include <stdio.h>
#include "rotaryEncoder.h"
#include <parameter.h>
#include "controlSurface.h"

#define VERSION_STRING  "0.2"

void testParameter(){

    Parameter delay("delay",0,-10,10,1.0);

    printf("%f\n",delay.getValue());
    delay.increment();
    printf("%f\n",delay.getValue());
    delay.increment(3);
    printf("%f\n",delay.getValue());
    delay.increment(10);
    printf("%f\n",delay.getValue());
    delay.reset();
    printf("%f\n",delay.getValue());

}

int main(int argc, char** argv){


    ControlSurface myControls;
    Parameter delay("delay",100,10,200,10);


    printf("effectControl V%s\n",VERSION_STRING);
    RotaryEncoder rot1("rot 1","/dev/input/event1");
    rot1.Init();
    rot1.start();

    myControls.addParameter(&delay);
    myControls.addControl(&rot1);
    myControls.assign("delay",0);

    while(1){

        
    }
    return 0;   
}
