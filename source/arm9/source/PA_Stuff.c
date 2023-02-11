#include <PA9.h>
#include <dirent.h>

void PA_SetVideoMode(u8 screen, u8 mode) {
	// NEW version
	if (screen) {
		REG_DISPCNT_SUB &= ~7;   // clear mode flags
		REG_DISPCNT_SUB |= mode; // set mode
	} else {
		REG_DISPCNT &= ~7;   // clear mode flags
		REG_DISPCNT |= mode; // set mode
	}
}