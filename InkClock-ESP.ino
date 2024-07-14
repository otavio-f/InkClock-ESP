#include "screen.h"
#include "clock.h"
#include "wificonn.h"
#include "webserver.h"
#include "app_params.h" // APP_... constants defined here

#define TZ_BR -10800

char timenow[64] = {0};

/**
 * For now this only tests if the functions are working properly
 */
void
setup()
{
  Serial.begin(115200);
  Serial.print("\n\nConnecting to wifi... ");
  int wifistatus = wifi_connect(APP_WIFI_SSID, APP_WIFI_PW, 15);
  if(wifistatus == CONN_OK)
    Serial.printf("Connected (%s).\n", get_local_ip().c_str());
  else
    Serial.printf("Error.\n");
  
  sync_time("pool.ntp.org", TZ_BR);
  get_time(timenow, sizeof(timenow), "%d/%m/%Y\n%H:%M");
  Serial.printf("time: %s, mins: %d, secs: %d\n", timenow, get_now_mins(), get_now_secs());
  switch(initialize_server(APP_SRV_MDNS_NAME, APP_SRV_PORT))
  {
    case SRV_OK:
      Serial.printf("Server initialized on port %d\n", APP_SRV_PORT);
      break;
    case SRV_FAIL:
      Serial.println("Failed to initialize server");
      break;
    case SRV_MDNS_FAIL:
      Serial.println("Failed to initialize MDNS");
      break;
    case SRV_STOR_FAIL:
      Serial.println("Failed to initialize server storage");
      break;
  }
  screen_init();
  show_text(timenow);
}

void
loop()
{
  wait_clients();
  delay(5);
}
