#include "../common/defines.h"

int main(void)
{
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
 
