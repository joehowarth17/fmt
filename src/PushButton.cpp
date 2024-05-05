#include "PushButton.h"
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <format>
#include "input.h"

PushButton::PushButton(std::string name,char *buttonEvent, int keycode): InputDevice(buttonEvent) , Control(name)
{
	key = keycode;

}


void PushButton::processInput(input_event *ev)
{
			unsigned int type, code;

			type = ev->type;
			code = ev->code;

			//printf("Event: %d time %ld.%06ld, ", code,ev->time.tv_sec, ev->time.tv_usec);

			if (type == EV_SYN) {
			
			} else {

				if(type == EV_KEY && code == key){
					
					if(ev->value == 0){
						std::cout << std::format("PB: Pressed, increment\n");
						param->increment();
					}else{
						std::cout << std::format("PB: Released\n");
					}
				}
			}
}