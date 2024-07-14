#ifndef __WIFICONN
#define __WIFICONN

#define CONN_OK 0
#define CONN_FAIL -1
#define CONN_UNKNOWN_FAIL -2

#include <WString.h>

int
wifi_connect(const char*, const char*, const int);

void
wifi_disconnect();

String
get_local_ip();

#endif
