#include "h7_host.h"
_Static_assert(sizeof(void *) == 4, "STM32H7 linker fixture requires a32-bit target");
_Static_assert(FLASH_WRITE_SIZE == 32,
               "Inspect actual source MCU support before adding another write width");
grbl_hal_t hal;
uint32_t h7_flash_words[64];
uint8_t *h7_source;
unsigned h7_unlocks, h7_locks, h7_erases, h7_programs, h7_fail_program;
bool h7_unlock_ok = true, h7_erase_ok = true;
static bool unlocked;
#ifdef _WIN32
__asm__(".globl __EEPROM_Emul_Start\n.set __EEPROM_Emul_Start, _h7_flash_words\n");
#else
__asm__(".globl _EEPROM_Emul_Start\n.set _EEPROM_Emul_Start, h7_flash_words\n");
#endif
void h7_prepare(unsigned size)
{
    CHECK(size && size <= 128 && !(size & 3));
    hal.nvs.size = size;
    h7_source = malloc(size);
    CHECK(h7_source);
    for (unsigned i = 0; i < size; i++)
        h7_source[i] = i + 1;
    memset(h7_flash_words, 0xff, sizeof(h7_flash_words));
}
HAL_StatusTypeDef HAL_FLASH_Unlock(void)
{
    CHECK(!unlocked);
    h7_unlocks++;
    unlocked = h7_unlock_ok;
    return unlocked ? HAL_OK : HAL_ERROR;
}
HAL_StatusTypeDef HAL_FLASH_Lock(void)
{
    CHECK(unlocked);
    unlocked = false;
    h7_locks++;
    return HAL_OK;
}
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *erase, uint32_t *error)
{
    CHECK(unlocked && erase && error);
    CHECK(erase->Sector == 7 && erase->TypeErase == FLASH_TYPEERASE_SECTORS &&
          erase->NbSectors == 1 && erase->VoltageRange == FLASH_VOLTAGE_RANGE_3);
#ifdef FLASH_BANK_2
    CHECK(erase->Banks == FLASH_BANK_2);
#else
    CHECK(erase->Banks == FLASH_BANK_1);
#endif
    h7_erases++;
    *error = h7_erase_ok ? 0xffffffff : 7;
    if (!h7_erase_ok)
        return HAL_ERROR;
    memset(h7_flash_words, 0xff, sizeof(h7_flash_words));
    return HAL_OK;
}
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t type, uint32_t address, uint32_t data_address)
{
    CHECK(unlocked && type == FLASH_TYPEPROGRAM_FLASHWORD);
    uintptr_t offset = (uintptr_t)address - (uintptr_t)h7_flash_words;
    CHECK(offset == h7_programs * FLASH_WRITE_SIZE && offset < hal.nvs.size);
    const uint8_t *data = (const uint8_t *)(uintptr_t)data_address;
    for (unsigned i = 0; i < FLASH_WRITE_SIZE; i++)
        CHECK(data[i] == (offset + i < hal.nvs.size ? h7_source[offset + i] : 0));
    h7_programs++;
    if (h7_fail_program == h7_programs)
        return HAL_ERROR;
    memcpy((uint8_t *)h7_flash_words + offset, data, FLASH_WRITE_SIZE);
    return HAL_OK;
}
void h7_check_copy(void)
{
    unsigned padded = (hal.nvs.size + FLASH_WRITE_SIZE - 1) / FLASH_WRITE_SIZE * FLASH_WRITE_SIZE;
    CHECK(!memcmp(h7_flash_words, h7_source, hal.nvs.size));
    for (unsigned i = hal.nvs.size; i < padded; i++)
        CHECK(((uint8_t *)h7_flash_words)[i] == 0);
    CHECK(((uint8_t *)h7_flash_words)[padded] == 255);
    CHECK(h7_unlocks == 1 && h7_erases == 1 && h7_programs == padded / FLASH_WRITE_SIZE &&
          h7_locks == 1 && !unlocked);
    uint8_t dest[132];
    memset(dest, 0x5a, sizeof(dest));
    CHECK(memcpy_from_flash(dest) && !memcmp(dest, h7_source, hal.nvs.size) &&
          dest[hal.nvs.size] == 0x5a);
}
void h7_close(void)
{
    free(h7_source);
    h7_source = NULL;
}
