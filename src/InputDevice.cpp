#include "InputDevice.h"
#include "input.h"

#include <stdio.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include "spdlog/spdlog.h"


InputDevice::InputDevice(char *path)
{
    strncpy(devicePath,path,MAX_DEV_LEN);
}

int InputDevice::Init()
{
    spdlog::debug("InputDevice opening device at path: {}",devicePath);
	if ((fd = open(devicePath, O_RDONLY)) < 0) {
		spdlog::error("Could not find input device {}: {}",devicePath,strerror(errno));
		return -1;
	}

	printDeviceInfo();
	
	return 0;

}

int InputDevice::start()
{
   	running=true;
	int res =pthread_create(&thread,NULL,InputDevice::_startMonitor,(void*)this);
	return res;
}

void *InputDevice::_startMonitor(void *param)
{
    	
	InputDevice* dev = (InputDevice*)param;
	dev->monitorThread();
	return NULL;
}
int InputDevice::stop()
{
 	running = false;
	pthread_join(thread,NULL);
	
	return 0;
}

void InputDevice::printDeviceInfo()
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

void InputDevice::monitorThread()
{

    
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
			 processInput(&ev[i]);
		}
        
	}

	ioctl(fd, EVIOCGRAB, (void*)0);
}

void InputDevice::processInput(input_event* ev)
{
unsigned int type, code;

			type = ev->type;
			code = ev->code;

			printf("Event: time %ld.%06ld, ", ev->time.tv_sec, ev->time.tv_usec);

			if (type == EV_SYN) {
				if (code == SYN_MT_REPORT)
					printf("++++++++++++++ %s ++++++++++++\n", codename(type, code));
				else if (code == SYN_DROPPED)
					printf(">>>>>>>>>>>>>> %s <<<<<<<<<<<<\n", codename(type, code));
				else
					printf("-------------- %s ------------\n", codename(type, code));
			} else {
				printf("type %d (%s), code %d (%s), ",
					type, eventTypename(type),
					code, codename(type, code));
				if (type == EV_MSC && (code == MSC_RAW || code == MSC_SCAN))
					printf("value %02x\n", ev->value);
				else
					printf("value %d\n", ev->value);
			}

}
