#include "clock.h"
#include <ctime>
#include <Arduino.h>

int
sync_time(const char *server, const int tz)
{
  configTime(tz, 0, server);
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
    return NTP_ERR;
    
  time_t tv_sec = mktime(&timeinfo);
  struct timeval tv = {.tv_sec=tv_sec, .tv_usec=0};
  if(settimeofday(&tv, NULL)==-1)
    return SYNC_ERR;
  return SYNC_OK;
}

struct tm
get_now_time()
{
  struct tm timeinfo;
  time_t now;
  time(&now);
  localtime_r(&now, &timeinfo);
  return timeinfo;
}

void
get_time(char *buf, const size_t len, const char *format)
{
  struct tm timeinfo = get_now_time();
  strftime(buf, len, format, &timeinfo);
}

int
get_now_mins()
{
  struct tm timeinfo = get_now_time();
  return timeinfo.tm_min;
}

int
get_now_secs()
{
  struct tm timeinfo = get_now_time();
  return timeinfo.tm_sec;
}
