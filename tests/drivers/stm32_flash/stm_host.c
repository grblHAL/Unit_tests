#include "stm_host.h"
_Static_assert(sizeof(void *) == 4, "STM32 linker-address fixture requires a32-bit host target");
grbl_hal_t hal;
uint32_t stm_flash_words[32];
uint16_t stm_source[64];
unsigned stm_unlocks, stm_locks, stm_erases, stm_programs, stm_erase_failures, stm_program_fail;
bool stm_unlock_ok = true;
static bool unlocked;
// These are linker symbols, not pointer objects: match the original .ld semantics.
#ifdef _WIN32
__asm__(".globl __EEPROM_Emul_Start\n.set __EEPROM_Emul_Start, _stm_flash_words\n.globl "
        "__EEPROM_Emul_Sector\n.set __EEPROM_Emul_Sector, 1\n");
#else
__asm__(".globl _EEPROM_Emul_Start\n.set _EEPROM_Emul_Start, stm_flash_words\n.globl "
        "_EEPROM_Emul_Sector\n.set _EEPROM_Emul_Sector, 1\n");
#endif
void stm_prepare(unsigned size)
{
    CHECK(size && size <= sizeof(stm_source) && !(size & 3));
    hal.nvs.size = size;
    memset(stm_flash_words, 0xff, sizeof(stm_flash_words));
    for (unsigned i = 0; i < 64; i++)
        stm_source[i] = 0x1200 + i;
    stm_unlocks = stm_locks = stm_erases = stm_programs = stm_erase_failures = stm_program_fail = 0;
    stm_unlock_ok = true;
    unlocked = false;
}
HAL_StatusTypeDef HAL_FLASH_Unlock(void)
{
    CHECK(!unlocked);
    stm_unlocks++;
    unlocked = stm_unlock_ok;
    return unlocked ? HAL_OK : HAL_ERROR;
}
HAL_StatusTypeDef HAL_FLASH_Lock(void)
{
    CHECK(unlocked);
    stm_locks++;
    unlocked = false;
    return HAL_OK;
}
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *erase, uint32_t *error)
{
    CHECK(unlocked && erase && error);
#if STM32_FAMILY == 4
    CHECK(erase->Banks == FLASH_BANK_1);
#endif
    CHECK(erase->Sector == 1 && erase->TypeErase == FLASH_TYPEERASE_SECTORS &&
          erase->NbSectors == 1 && erase->VoltageRange == FLASH_VOLTAGE_RANGE_3);
    stm_erases++;
    if (stm_erase_failures)
    {
        stm_erase_failures--;
        *error = 1;
        return HAL_ERROR;
    }
    memset(stm_flash_words, 0xff, sizeof(stm_flash_words));
    *error = 0xffffffff;
    return HAL_OK;
}
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t type, uint32_t address, uint64_t value)
{
    CHECK(unlocked && type == FLASH_TYPEPROGRAM_HALFWORD && value <= 0xffff);
    uintptr_t offset = (uintptr_t)address - (uintptr_t)stm_flash_words;
    CHECK(!(offset & 1) && offset + 2 <= hal.nvs.size && offset == 2 * stm_programs);
    stm_programs++;
    if (stm_program_fail == stm_programs)
        return HAL_ERROR;
    uint16_t v = (uint16_t)value;
    memcpy((uint8_t *)stm_flash_words + offset, &v, 2);
    return HAL_OK;
}
void stm_check_copy(void)
{
    CHECK(!memcmp(stm_flash_words, stm_source, hal.nvs.size));
    uint8_t readback[132];
    memset(readback, 0x5a, sizeof(readback));
    CHECK(memcpy_from_flash(readback));
    CHECK(!memcmp(readback, stm_source, hal.nvs.size) && readback[hal.nvs.size] == 0x5a);
    CHECK(stm_unlocks == 1 && stm_locks == 1 && stm_programs == hal.nvs.size / 2);
}
