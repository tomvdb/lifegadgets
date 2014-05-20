#include "timers.h"

static volatile uint32_t TimingDelay;
void TimingDelay_Decrement(void);

void initClock(void)
{

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_SYSCFG , ENABLE);

  // divide HCLK / 2
  RCC_HCLKConfig(RCC_SYSCLK_Div2);

  // enable HSI
  RCC_HSICmd(ENABLE);
  RCC_PLLCmd(DISABLE);

  // wait for HSI to get ready
  while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

  // configure PLL - x4 /2 
  RCC_PLLConfig( RCC_PLLSource_HSI, RCC_PLLMul_8,  RCC_PLLDiv_4 );
  RCC_PLLCmd(ENABLE);

  while ( RCC_GetFlagStatus( RCC_FLAG_PLLRDY ) == RESET );

  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  SysTick_Config((RCC_Clocks.SYSCLK_Frequency / 2) / 1000); // Cannot exceed 16,777,215

  /* Set SysTick Preemption Priority, it's a system handler rather than a regular interrupt */
  NVIC_SetPriority(SysTick_IRQn, 0x04);

  // setup lse for rtc
  PWR_RTCAccessCmd(ENABLE);  

  // Reset RTC Backup Domain 
  RCC_RTCResetCmd(ENABLE);
  RCC_RTCResetCmd(DISABLE);

  // LSE Enable
  RCC_LSEConfig(RCC_LSE_ON);

  // Wait until LSE is ready 
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
  
  // RTC Clock Source Selection 
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); 
  
  // Enable the RTC 
  RCC_RTCCLKCmd(ENABLE); 

  RTC_WaitForSynchro();    

}

void resetRTC()
{
  // init rtc
  RTC_InitTypeDef rtcInit;
  rtcInit.RTC_HourFormat = RTC_HourFormat_24;
  rtcInit.RTC_AsynchPrediv = 0x7F; 
  rtcInit.RTC_SynchPrediv = 0xFF; 
  RTC_Init(&rtcInit);  

  // Set the time (BCD)
  RTC_TimeTypeDef RTC_TimeStructure;
  RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
  RTC_TimeStructure.RTC_Hours   = 0x00;
  RTC_TimeStructure.RTC_Minutes = 0x00;
  RTC_TimeStructure.RTC_Seconds = 0x00;
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);
}

void delayms(uint32_t nTime)
{
  TimingDelay = nTime;
  while(TimingDelay != 0);
}
 
// Called from SysTick_Handler
 
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00){
    TimingDelay--;}
}
 
void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}