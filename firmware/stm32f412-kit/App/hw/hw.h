#ifndef HW_H_
#define HW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hw_def.h"

#include "led.h"
#include "uart.h"
#include "log.h"
#include "cli.h"
#include "i2c.h"
#include "eeprom.h"
#include "spi.h"
#include "spi_flash.h"
#include "gpio.h"
#include "rtc.h"
#include "sd.h"
#include "fatfs.h"
#include "files.h"
#include "imu.h"
#include "hdc1080.h"


bool hwInit(void);


#ifdef __cplusplus
}
#endif

#endif