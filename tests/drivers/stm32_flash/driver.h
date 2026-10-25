#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "grbl/hal.h"
#define FLASH_ENABLE 1
// Host HAL boundary; layouts follow each selected family's original HAL headers.
typedef enum
{
    HAL_OK = 0,
    HAL_ERROR = 1,
    HAL_BUSY = 2,
    HAL_TIMEOUT = 3
} HAL_StatusTypeDef;
typedef struct
{
    uint32_t TypeErase;
#if STM32_FAMILY == 1
    uint32_t Banks, PageAddress, NbPages;
#else
#if STM32_FAMILY == 4
    uint32_t Banks;
#endif
    uint32_t Sector, NbSectors, VoltageRange;
#endif
} FLASH_EraseInitTypeDef;
#define FLASH_BANK_1 1U
#define FLASH_TYPEERASE_SECTORS 0U
#define FLASH_TYPEERASE_PAGES 0U
#define FLASH_VOLTAGE_RANGE_3 2U
#define FLASH_TYPEPROGRAM_HALFWORD 1U
HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *erase, uint32_t *error);
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t type, uint32_t address, uint64_t value);
