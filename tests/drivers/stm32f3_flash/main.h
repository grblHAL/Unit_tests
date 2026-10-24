#pragma once
#include <stdint.h>
#include <stdbool.h>
#define FLASH_BASE 0x08000000U
#define FLASH_SIZE_DATA_REGISTER 0x1FFFF7CCU
#define FLASH_PAGE_SIZE 2048U
#define FLASH_TYPEERASE_PAGES 0U
#define FLASH_TYPEPROGRAM_HALFWORD 1U
typedef enum
{
    HAL_OK = 0,
    HAL_ERROR = 1,
    HAL_BUSY = 2,
    HAL_TIMEOUT = 3
} HAL_StatusTypeDef;
typedef struct
{
    uint32_t TypeErase, PageAddress, NbPages;
} FLASH_EraseInitTypeDef;
HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *erase, uint32_t *error);
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t type, uint32_t address, uint64_t value);
