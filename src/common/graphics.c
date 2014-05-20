#include "graphics.h"

void showLogo(void)
{
	lcdClear();

  	for ( int i = 0; i < ( 84 * 48 ) / 8; i++)
  	{
    	lcdWrite(LCD_DATA, logo[i]);
  	}
}
