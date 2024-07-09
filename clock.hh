#ifndef __CLOCK
#define __CLOCK

#include <cstddef>
#include <cstdint>

#define NTP_ERR -1
#define SYNC_ERR -2
#define SYNC_OK 0

int
sync_time(const char*, const int);

void
get_time(char*,  const size_t, const char*);

int
get_now_mins();

int
get_now_secs();

#endif
