#include "adc.h"



#ifdef _USE_HW_ADC
#include "cli.h"
#include "cli_gui.h"


#define NAME_DEF(x)  x, #x

#ifdef _USE_HW_RTOS
#define lock()      xSemaphoreTake(mutex_lock, portMAX_DELAY);
#define unLock()    xSemaphoreGive(mutex_lock);
#else
#define lock()      
#define unLock()    
#endif


typedef struct
{
  ADC_HandleTypeDef  *p_hadc;
  uint32_t            channel;  
  uint32_t            rank;  
  AdcPinName_t        pin_name;
  const char         *p_name;
} adc_tbl_t;


#if CLI_USE(HW_ADC)
static void cliAdc(cli_args_t *args);
#endif


extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

#ifdef _USE_HW_RTOS
static SemaphoreHandle_t mutex_lock;
#endif
static bool is_init = false;

__attribute__((section(".non_cache")))
static uint16_t adc_data_buf[ADC_MAX_CH];


static const adc_tbl_t adc_tbl[ADC_MAX_CH] = 
  {
    {&hadc1, ADC_CHANNEL_0          , 1 , NAME_DEF(LIGHT_ADC)     },
  };




bool adcInit(void)
{
  bool ret = true;  

#ifdef _USE_HW_RTOS
  mutex_lock = xSemaphoreCreateMutex();
#endif


  if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adc_data_buf[0], hadc1.Init.NbrOfConversion) != HAL_OK)
  {
    ret = false;
  }    
  is_init = ret;
  
  logPrintf("[%s] adcInit()\n", is_init ? "OK":"NG");

#if CLI_USE(HW_ADC)
  cliAdd("adc", cliAdc);
#endif
  return ret;
}

bool adcIsInit(void)
{
  return is_init;
}

int32_t adcRead(uint8_t ch)
{
  assert_param(ch < ADC_MAX_CH);

  return adc_data_buf[ch];
}

int32_t adcRead8(uint8_t ch)
{
  return adcRead(ch)>>4;
}

int32_t adcRead10(uint8_t ch)
{
  return adcRead(ch)>>2;
}

int32_t adcRead12(uint8_t ch)
{
  return adcRead(ch)>>0;
}

int32_t adcRead16(uint8_t ch)
{
  return adcRead(ch)<<4;  
}

uint8_t adcGetRes(uint8_t ch)
{
  (void)ch;

  return 12;
}

float adcReadVoltage(uint8_t ch)
{
  return adcConvVoltage(ch, adcRead(ch));
}

float adcConvVoltage(uint8_t ch, uint32_t adc_value)
{
  float ret = 0;


  switch (ch)
  {
    default :
      ret  = ((float)adc_value * 3.3f) / (4095.f);
      break;
  }

  return ret;
}

#if CLI_USE(HW_ADC)
void cliAdc(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "info") == true)
  {
    cliPrintf("adc init : %d\n", is_init);
    cliPrintf("adc res  : %d\n", adcGetRes(0));
    for (int i=0; i<ADC_MAX_CH; i++)
    {
      cliPrintf("%02d. %-32s : %04d\n", i, adc_tbl[i].p_name, adcRead(i));
    }

    ret = true;
  }

  if (args->argc == 1 && args->isStr(0, "show") == true)
  {
    cliShowCursor(false);
    while(cliKeepLoop())
    {
      for (int i=0; i<ADC_MAX_CH; i++)
      {
        cliPrintf("%02d. %-32s : %04d \n", i, adc_tbl[i].p_name, adcRead(i));
      }
      delay(50);
      cliPrintf("\x1B[%dA", ADC_MAX_CH);
    }
    cliPrintf("\x1B[%dB", ADC_MAX_CH);
    cliShowCursor(true);
    ret = true;
  }

  if (args->argc == 2 && args->isStr(0, "show") && args->isStr(1, "vol"))
  {
    cliShowCursor(false);
    while(cliKeepLoop())
    {
      for (int i=0; i<ADC_MAX_CH; i++)
      {
        float adc_data;

        adc_data = adcReadVoltage(i);

        cliPrintf("%02d. %-32s : %d.%02dV \n",i, adc_tbl[i].p_name, (int)adc_data, (int)(adc_data * 100)%100);
      }
      delay(50);
      cliPrintf("\x1B[%dA", ADC_MAX_CH);
    }
    cliPrintf("\x1B[%dB", ADC_MAX_CH);
    cliShowCursor(true);
    ret = true;
  }

  if (ret != true)
  {
    cliPrintf("adc info\n");
    cliPrintf("adc show\n");
    cliPrintf("adc show vol\n");
  }
}
#endif

#endif