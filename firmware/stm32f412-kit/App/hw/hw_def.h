#ifndef HW_DEF_H_
#define HW_DEF_H_


#include "main.h"
#include "def.h"


#define _DEF_FIRMWATRE_VERSION    "V240904R1"
#define _DEF_BOARD_NAME           "STM32F412-KIT-FW"


#define _USE_HW_SD
#define _USE_HW_FATFS
#define _USE_HW_FILES
#define _USE_HW_IMU
#define _USE_HW_ICM42670
#define _USE_HW_HDC1080 


#define _USE_HW_LED
#define      HW_LED_MAX_CH          1

#define _USE_HW_UART
#define      HW_UART_MAX_CH         1
#define      HW_UART_CH_SWD         _DEF_UART1
#define      HW_UART_CH_CLI         _DEF_UART1

#define _USE_HW_LOG
#define      HW_LOG_CH              _DEF_UART1
#define      HW_LOG_BOOT_BUF_MAX    2048
#define      HW_LOG_LIST_BUF_MAX    4096

#define _USE_HW_CLI
#define      HW_CLI_CMD_LIST_MAX    32
#define      HW_CLI_CMD_NAME_MAX    16
#define      HW_CLI_LINE_HIS_MAX    8
#define      HW_CLI_LINE_BUF_MAX    64

#define _USE_HW_I2C
#define      HW_I2C_MAX_CH          1
#define      HW_I2C_CH_EEPROM       _DEF_I2C1
#define      HW_I2C_CH_IMU          _DEF_I2C1

#define _USE_HW_EEPROM
#define      HW_EEPROM_MAX_SIZE     (8*1024)

#define _USE_HW_SPI
#define      HW_SPI_MAX_CH          1

#define _USE_HW_GPIO
#define      HW_GPIO_MAX_CH         GPIO_PIN_MAX

#define _USE_HW_SPI_FLASH
#define      HW_SPI_FLASH_ADDR      0x91000000

#define _USE_HW_RTC
#define      HW_RTC_BOOT_MODE       RTC_BKP_DR3
#define      HW_RTC_RESET_BITS      RTC_BKP_DR4

#define _USE_HW_ADC                 
#define      HW_ADC_MAX_CH          ADC_PIN_MAX


//-- USE CLI
//
#define _USE_CLI_HW_EEPROM          1
#define _USE_CLI_HW_SPI_FLASH       1
#define _USE_CLI_HW_RTC             1
#define _USE_CLI_HW_SD              1
#define _USE_CLI_HW_FATFS           1
#define _USE_CLI_HW_IMU             1
#define _USE_CLI_HW_HDC1080         1
#define _USE_CLI_HW_ADC             1


typedef enum
{
  SPI_FLASH_CS,
  SD_CD,
  GPIO_PIN_MAX,
} GpioPinName_t;

typedef enum
{
  LIGHT_ADC = 0,
  ADC_PIN_MAX
} AdcPinName_t;


void     logPrintf(const char *fmt, ...);
void     delay(uint32_t time_ms);
uint32_t millis(void);
uint32_t micros(void);

#endif