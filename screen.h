#ifndef __SCREEN
#define __SCREEN

#include <WString.h>
#include <cstdint>

#define ORIENT_LEFT 1
#define ORIENT_RIGHT 2
#define ORIENT_CENTER_H 4
#define ORIENT_TOP 8
#define ORIENT_BOTTOM 16
#define ORIENT_CENTER_V 32

void
screen_init();

void
screen_print_aligned(const String, const uint8_t);

void
screen_print_absolute(const String, const uint16_t, const uint16_t);

void
screen_clear();

#endif
