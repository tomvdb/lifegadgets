#include "system.h"

void initSystem(void)
{
  // init clocks
  initClock(); 
  resetRTC();

  #ifdef OUTPUT_GADGET

  	lcdInit();

  #endif

}
