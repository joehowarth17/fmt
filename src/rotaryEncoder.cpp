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

RotaryEncoder::RotaryEncoder(char* rotaryEvent){

	strncpy(devicePath,rotaryEvent,MAX_DEV_LEN);
	
}

int RotaryEncoder::Init()
{

	if ((fd = open(devicePath, O_RDONLY)) < 0) {
		perror("evtest");
		return 1;
	}

	printDeviceInfo();
	
	return 0;
}

void* RotaryEncoder::_startMonitor(void * param){

	if(ROT_DEBUG)printf("starting rotary thread\n");
	RotaryEncoder* encoder = (RotaryEncoder*)param;
	encoder->monitorThread();
	return NULL;
}



int RotaryEncoder::start(){

	running=true;
	int res =pthread_create(&rotaryThread,NULL,RotaryEncoder::_startMonitor,(void*)this);
	return res;
}

int RotaryEncoder::stop(){

	running = false;
	pthread_join(rotaryThread,NULL);
	if(ROT_DEBUG)printf("Stopped rotary encoder\n");
	return 0;
}

static inline const char* codename(unsigned int type, unsigned int code)
{
	return (type <= EV_MAX && code <= maxval[type] && names[type] && names[type][code]) ? names[type][code] : "?";
}

void RotaryEncoder::monitorThread(){

	if(ROT_DEBUG)printf("Monitoring rotary encoder\n");
	
	struct input_event ev[64];
	int i, rd;
	fd_set rdfs;

	FD_ZERO(&rdfs);
	FD_SET(fd, &rdfs);

	while(running){
		
		select(fd + 1, &rdfs, NULL, NULL, NULL);
		if (!running)
			break;

		rd = read(fd, ev, sizeof(ev));

		if (rd < (int) sizeof(struct input_event)) {
			printf("expected %d bytes, got %d\n", (int) sizeof(struct input_event), rd);
			perror("\nevtest: error reading");
			running = false;
		}

		for (i = 0; i < rd / sizeof(struct input_event); i++) {
			unsigned int type, code;

			type = ev[i].type;
			code = ev[i].code;

			//printf("Event: time %ld.%06ld, ", ev[i].time.tv_sec, ev[i].time.tv_usec);

			if (type == EV_SYN) {
				// if (code == SYN_MT_REPORT)
				// 	printf("++++++++++++++ %s ++++++++++++\n", codename(type, code));
				// else if (code == SYN_DROPPED)
				// 	printf(">>>>>>>>>>>>>> %s <<<<<<<<<<<<\n", codename(type, code));
				// else
				// 	printf("-------------- %s ------------\n", codename(type, code));
			} else {
				// printf("type %d (%s), code %d (%s), ",
				// 	type, eventTypename(type),
				// 	code, codename(type, code));
				// if (type == EV_MSC && (code == MSC_RAW || code == MSC_SCAN))
				// 	printf("value %02x\n", ev[i].value);
				// else
				// 	printf("value %d\n", ev[i].value);
				if(type == EV_REL && code == REL_X){

					if(ev[i].value == 1){ 
						param->increment();
					}
					else{
						param->decrement();
					}
				}
			}
		}

	}

	ioctl(fd, EVIOCGRAB, (void*)0);
	

	
}

int RotaryEncoder::getAngle()
{

    return 0;
}


void RotaryEncoder::printDeviceInfo()
{

	int version;
	
	unsigned short id[4];
	char name[256] = "Unknown";
	if (ioctl(fd, EVIOCGVERSION, &version)) {
		perror("evtest: can't get version");
	}

	printf("Input driver version is %d.%d.%d\n",
		version >> 16, (version >> 8) & 0xff, version & 0xff);

	ioctl(fd, EVIOCGID, id);
	printf("Input device ID: bus 0x%x vendor 0x%x product 0x%x version 0x%x\n",
		id[ID_BUS], id[ID_VENDOR], id[ID_PRODUCT], id[ID_VERSION]);

	ioctl(fd, EVIOCGNAME(sizeof(name)), name);
	printf("Input device name: \"%s\"\n", name);

}
