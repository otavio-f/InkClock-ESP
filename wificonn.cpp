#include "wificonn.h"
#include <WiFi.h>
#include <WString.h>


int
wifi_connect(const char *ssid, const char *passwd, const int timeout)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwd);
  for(int t=timeout; t--;)
  {
    switch(WiFi.status())
    {
      case WL_DISCONNECTED:
        delay(1000);
        break;
      case WL_CONNECTED:
        return CONN_OK;
      case WL_CONNECT_FAILED:
        return CONN_FAIL;
      default:
        return CONN_UNKNOWN_FAIL;
    }
  }
}


void
wifi_disconnect()
{
  WiFi.disconnect();
}

String
get_local_ip()
{
  return WiFi.localIP().toString();
}
