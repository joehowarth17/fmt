#ifdef LINUX
#include "rotaryEncoder.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <pthread.h>

#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "input.h"

#define ROT_DEBUG	(0)

#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)

RotaryEncoder::RotaryEncoder(std::string name, char* rotaryEvent): InputDevice(rotaryEvent), Control (name){

}

void RotaryEncoder::processInput(input_event *ev)
{
				unsigned int type, code;

			type = ev->type;
			code = ev->code;

			//printf("Event: time %ld.%06ld, ", ev[i].time.tv_sec, ev[i].time.tv_usec);

			if (type == EV_SYN) {
			
			} else {

				if(type == EV_REL && code == REL_X){

					if(ev->value == 1){ 
						param->increment();
					}
					else{
						param->decrement();
					}
				}
			}
}

// int RotaryEncoder::Init()
// {

// 	if ((fd = open(devicePath, O_RDONLY)) < 0) {
// 		perror("evtest");
// 		return 1;
// 	}

// 	printDeviceInfo();
	
// 	return 0;
// }

// void* RotaryEncoder::_startMonitor(void * param){

// 	if(ROT_DEBUG)printf("starting rotary thread\n");
// 	RotaryEncoder* encoder = (RotaryEncoder*)param;
// 	encoder->monitorThread();
// 	return NULL;
// }



// int RotaryEncoder::start(){

// 	running=true;
// 	int res =pthread_create(&rotaryThread,NULL,RotaryEncoder::_startMonitor,(void*)this);
// 	return res;
// }

// int RotaryEncoder::stop(){

// 	running = false;
// 	pthread_join(rotaryThread,NULL);
// 	if(ROT_DEBUG)printf("Stopped rotary encoder\n");
// 	return 0;
// }



// void RotaryEncoder::monitorThread(){

// 	if(ROT_DEBUG)printf("Monitoring rotary encoder\n");
	
// 	struct input_event ev[64];
// 	int i, rd;
// 	fd_set rdfs;

// 	FD_ZERO(&rdfs);
// 	FD_SET(fd, &rdfs);

// 	while(running){
		
// 		select(fd + 1, &rdfs, NULL, NULL, NULL);
// 		if (!running)
// 			break;

// 		rd = read(fd, ev, sizeof(ev));

// 		if (rd < (int) sizeof(struct input_event)) {
// 			printf("expected %d bytes, got %d\n", (int) sizeof(struct input_event), rd);
// 			perror("\nevtest: error reading");
// 			running = false;
// 		}

// 		for (i = 0; i < rd / sizeof(struct input_event); i++) {
// 			unsigned int type, code;

// 			type = ev[i].type;
// 			code = ev[i].code;

// 			//printf("Event: time %ld.%06ld, ", ev[i].time.tv_sec, ev[i].time.tv_usec);

// 			if (type == EV_SYN) {
			
// 			} else {

// 				if(type == EV_REL && code == REL_X){

// 					if(ev[i].value == 1){ 
// 						param->increment();
// 					}
// 					else{
// 						param->decrement();
// 					}
// 				}
// 			}
// 		}

// 	}

// 	ioctl(fd, EVIOCGRAB, (void*)0);
	
// }


// void RotaryEncoder::printDeviceInfo()
// {

// 	int version;
	
// 	unsigned short id[4];
// 	char name[256] = "Unknown";
// 	if (ioctl(fd, EVIOCGVERSION, &version)) {
// 		perror("evtest: can't get version");
// 	}

// 	printf("Input driver version is %d.%d.%d\n",
// 		version >> 16, (version >> 8) & 0xff, version & 0xff);

// 	ioctl(fd, EVIOCGID, id);
// 	printf("Input device ID: bus 0x%x vendor 0x%x product 0x%x version 0x%x\n",
// 		id[ID_BUS], id[ID_VENDOR], id[ID_PRODUCT], id[ID_VERSION]);

// 	ioctl(fd, EVIOCGNAME(sizeof(name)), name);
// 	printf("Input device name: \"%s\"\n", name);

// }
#endif