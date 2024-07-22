#include "wificonn.h"
#include <WiFi.h>


void
wifi_reset()
{
  switch(WiFi.getMode())
  {
    case WIFI_AP:
      WiFi.softAPdisconnect();
      break;
    case WIFI_STA:
      WiFi.disconnect();
      break;
  }
  WiFi.mode(WIFI_MODE_NULL);
  WiFi.setHostname("espserver");
}


void
wifi_generate(const char *ssid, const char *passwd)
{
  wifi_reset();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, passwd);
}


int
wifi_connect(const char *ssid, const char *passwd, const int timeout)
{
  wifi_reset();
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


String
get_local_ip()
{
  if(WiFi.getMode() == WIFI_MODE_AP)
    return WiFi.softAPIP().toString();

  return WiFi.localIP().toString();
}
