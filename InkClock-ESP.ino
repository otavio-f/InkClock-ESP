#include "screen.h"
#include "clock.h"
#include "wificonn.h"
#include "secrets.h" // define WIFI_SSID and WIFI_PW

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
  int wifistatus = wifi_connect(WIFI_SSID, WIFI_PW, 15);
  if(wifistatus == CONN_OK)
    Serial.printf("Connected.\n");
  else
    Serial.printf("Error.\n");
  
  sync_time("pool.ntp.org", TZ_BR);
  get_time(timenow, sizeof(timenow), "%d/%m/%Y\n%H:%M");
  Serial.printf("time: %s, mins: %d, secs: %d\n", timenow, get_now_mins(), get_now_secs());
  screen_init();
  show_text(timenow);
}

void
loop()
{
}
