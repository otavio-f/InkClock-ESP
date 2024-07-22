#ifndef __WIFICONN
#define __WIFICONN

#define CONN_OK 0
#define CONN_FAIL -1
#define CONN_UNKNOWN_FAIL -2

#include <WString.h>

void
wifi_generate(const char*, const char*);

int
wifi_connect(const char*, const char*, const int);

String
get_local_ip();

#endif
