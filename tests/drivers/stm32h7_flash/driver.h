#pragma once
#include "grbl/hal.h"
#define FLASH_ENABLE 1
#define FLASH_SECTOR_TOTAL 8U
#define FLASH_BANK_1 1U
#if defined(STM32H743xx)
#define FLASH_BANK_2 2U
#elif !defined(STM32H723xx)
#error Select a supported host MCU configuration
#endif
#define FLASH_TYPEERASE_SECTORS 0U
#define FLASH_VOLTAGE_RANGE_3 2U
#define FLASH_TYPEPROGRAM_FLASHWORD 1U
typedef enum
{
    HAL_OK = 0,
    HAL_ERROR = 1,
    HAL_BUSY = 2,
    HAL_TIMEOUT = 3
} HAL_StatusTypeDef;
typedef struct
{
    uint32_t TypeErase, Banks, Sector, NbSectors, VoltageRange;
} FLASH_EraseInitTypeDef;
HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *erase, uint32_t *error);
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t type, uint32_t address, uint32_t data_address);
