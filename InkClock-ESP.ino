#include "screen.hh"

void
setup()
{
  Serial.begin(115200);
  screen_init();
  show_text("Test");
}

void
loop()
{

}
