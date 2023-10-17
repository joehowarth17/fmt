#ifndef INPUT_H_
#define INPUT_H_

#include <linux/input.h>

extern const char * const events[EV_MAX + 1];
extern const int maxval[EV_MAX + 1];
extern const char * const * const names[EV_MAX + 1];
extern inline const char* eventTypename(unsigned int type)
{
	return (type <= EV_MAX && events[type]) ? events[type] : "?";
}
extern inline const char* codename(unsigned int type, unsigned int code)
{
	return (type <= EV_MAX && code <= maxval[type] && names[type] && names[type][code]) ? names[type][code] : "?";
}
int test_grab(int fd, int grab_flag);
#endif