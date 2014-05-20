#include "../common/defines.h"


int main(void)
{
  int prevSecond = -1;
  int blink = 0;

  // init gadget
  initSystem();
	showLogo();

  // read version
  // read batt voltage
  // init radio

  currentState = STATE_DISCONNECTED;
  delayms(2000);
  
  while (1)
  {
    // every loop check (might need to move to a timer interrupt)
    // update clock
    RTC_TimeTypeDef RTC_TimeStructure;
    char strDisp[20];
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure );

    if ( RTC_TimeStructure.RTC_Seconds != prevSecond )
    { 
      if ( blink == 1 )
      {
        mini_snprintf( strDisp, 10,  "%02d:%02d", RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes );
        blink = 0;
      }
      else
      {
        mini_snprintf( strDisp, 10,  "%02d %02d", RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes );
        blink = 1;
      }

      lcdClear();
      // lcdXY(1,5);
      lcdXY(45,5);
      lcdStr( strDisp );
      prevSecond = RTC_TimeStructure.RTC_Seconds;
    }


    // update battstatus

    switch( currentState )
    {
      case STATE_IDLE:
      {
          // check if state needs to change
          break;
      }

      case STATE_DISCONNECTED:
      {
          // announce to base station
          //  -- send id
          //  -- send batt status
          //  -- send version
          //  -- get current status
          break;
      }

      case STATE_OUTPUTACTIVE:
      {
          // get state data
          // check if state needs to change
          break;
      }

    }
  }

}
 
