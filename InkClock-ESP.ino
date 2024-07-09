#include "screen.hh"
#include "clock.hh"
#define TIMELEN 64
#define TZ_BR -10800

char timenow[TIMELEN] = {0};

/**
 * For now this only tests if the functions are working properly
 */
void
setup()
{
  Serial.begin(115200);
  sync_time("test", TZ_BR);
  get_time(timenow, sizeof(timenow), "%d/%m/%Y");
  Serial.printf("time: %s, mins: %d, secs: %d\n", timenow, get_now_mins(), get_now_secs());
  screen_init();
  show_text(timenow);
}

void
loop()
{
}
