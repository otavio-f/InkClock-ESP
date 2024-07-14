#ifndef __WEBSERVER
#define __WEBSERVER

#define SRV_OK 0
#define SRV_FAIL -1
#define SRV_MDNS_FAIL -2
#define SRV_STOR_FAIL -3

#include <cstdint>

int
initialize_server(const char*, const uint16_t);

void
wait_clients();

#endif
