#ifndef FATFS_H_
#define FATFS_H_

#include "hw_def.h"


#ifdef _USE_HW_FATFS


bool fatfsInit(void);
bool fatfsReInit(void);


#endif

#endif /* SRC_COMMON_HW_INCLUDE_FATFS_H_ */
