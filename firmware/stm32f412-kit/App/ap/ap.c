#include "ap.h"




void apInit(void)
{
  cliOpen(HW_UART_CH_CLI, 115200);
  cliLogo();  
}


void apMain(void)
{
  static uint32_t pre_time = 0;


  while(1)
  {  
    if (millis() - pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }
    cliMain();
  }
}
