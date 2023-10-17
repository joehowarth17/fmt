#include "PushButton.h"
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "input.h"

PushButton::PushButton(char *buttonEvent, int keycode): InputDevice(buttonEvent)
{
	key = keycode;
}


void PushButton::processInput(input_event *ev)
{
			unsigned int type, code;

			type = ev->type;
			code = ev->code;

			//printf("Event: time %ld.%06ld, ", ev[i].time.tv_sec, ev[i].time.tv_usec);

			if (type == EV_SYN) {
			
			} else {

				if(type == EV_KEY && code == key){



				}
			}
}