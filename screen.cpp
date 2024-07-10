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
show_text(String text)
{	
	int16_t x, y;
	uint16_t w, h;
	display.getTextBounds(text, 0, 0, &x, &y, &w, &h);
	x = (GxEPD_HEIGHT-w)/2;
	y = (GxEPD_WIDTH-h)/2;

	display.setCursor((GxEPD_HEIGHT-w)/2, (GxEPD_WIDTH-h)/2);
	display.fillScreen(GxEPD_WHITE);
	display.print(text);
	display.update();
}
