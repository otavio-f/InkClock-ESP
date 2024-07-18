#include "screen.h"

#define LILYGO_T5_V213
#include <boards.h>

#include <GxEPD.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>

GxIO_Class io(SPI, EPD_CS, EPD_DC, EPD_RSET);
GxEPD_Class display(io, EPD_RSET, EPD_BUSY);


void
screen_init()
{
	SPI.begin(EPD_SCLK, EPD_MISO, EPD_MOSI);
	display.init();
	display.setRotation(1);
	display.setFont(&FreeMonoBold18pt7b);
	display.setTextColor(GxEPD_BLACK);
}

void
screen_print_aligned(const String text, const uint8_t align)
{
	int16_t x, y;
	uint16_t w, h;
	display.getTextBounds(text, 0, 0, &x, &y, &w, &h);

  if(align & ORIENT_CENTER_H)
	  x = (get_width()-w)/2;
  else if(align & ORIENT_RIGHT)
    x = get_width()-w;
  else
    x = 0;

  if(align & ORIENT_CENTER_V)
	  y = (get_height()-h)/2;
  else if(align & ORIENT_BOTTOM)
    y = get_height()-h;
  else
    y = 0;

  screen_print_absolute(text, x, y);
}

void
screen_print_absolute(const String text, const uint16_t x, const uint16_t y)
{
  display.setCursor(x, y);
  display.print(text);
  display.update();
}

void
screen_clear()
{
  display.fillScreen(GxEPD_WHITE);
}

uint16_t
get_width()
{
  const int rotation = display.getRotation();
  if(rotation == 1 || rotation == 3)
    return GxEPD_HEIGHT;
  else
    return GxEPD_WIDTH;
}

uint16_t
get_height()
{
  const int rotation = display.getRotation();
  if(rotation == 1 || rotation == 3)
    return GxEPD_WIDTH;
  else
    return GxEPD_HEIGHT;
}
