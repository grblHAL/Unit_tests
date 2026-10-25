#pragma once
#include <stdint.h>
#define IAP_CMD_SUCCESS 0
#define IAP_SECTOR_NOT_BLANK 8
#define IAP_SECTOR_NOT_PREPARED 9
#define IAP_BUSY 11
void __disable_irq(void);
void __enable_irq(void);
uint8_t Chip_IAP_PreSectorForReadWrite(uint32_t first, uint32_t last);
uint8_t Chip_IAP_EraseSector(uint32_t first, uint32_t last);
uint8_t Chip_IAP_CopyRamToFlash(uint32_t address, uint32_t *source, uint32_t size);
