#include "system.h"

void initSystem(void)
{
  // init clocks
  initClock(); 

  #ifdef OUTPUT_GADGET

  	lcdInit();

  #endif

}
