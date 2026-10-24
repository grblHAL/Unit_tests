#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#undef NEAR
#else
#include <sys/mman.h>
#endif
#include "f3_host.h"
_Static_assert(sizeof(void *) == 4, "STM32F3 fixture requires a32-bit host target");
grbl_hal_t hal;
uint16_t f3_source[1024];
unsigned f3_unlocks, f3_locks, f3_erases, f3_programs, f3_fail_program;
bool f3_unlock_ok = true, f3_erase_ok = true;
uintptr_t f3_address;
static bool unlocked;
static void map_region(uintptr_t address, unsigned size)
{
#ifdef _WIN32
    void *mapped = VirtualAlloc((void *)address, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
    void *mapped = mmap((void *)address, size, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
#endif
    CHECK(mapped == (void *)address);
}
void f3_prepare(unsigned kb, unsigned size)
{
    CHECK((kb == 128 || kb == 256) && size && size <= sizeof(f3_source) && !(size & 3));
    static bool mapped;
    if (!mapped)
    {
        map_region(FLASH_BASE, 256 * 1024);
        map_region(0x1fff0000, 65536);
        mapped = true;
    }
    *(uint16_t *)FLASH_SIZE_DATA_REGISTER = kb;
    f3_address = FLASH_BASE + kb * 1024 - 4096;
    hal.nvs.size = size;
    memset((void *)FLASH_BASE, 0xff, 256 * 1024);
    memset((void *)f3_address, 0, FLASH_PAGE_SIZE);
    for (unsigned i = 0; i < 1024; i++)
        f3_source[i] = 0x5100 + i;
    f3_unlocks = f3_locks = f3_erases = f3_programs = f3_fail_program = 0;
    f3_unlock_ok = f3_erase_ok = true;
    unlocked = false;
}
HAL_StatusTypeDef HAL_FLASH_Unlock(void)
{
    CHECK(!unlocked);
    f3_unlocks++;
    unlocked = f3_unlock_ok;
    return unlocked ? HAL_OK : HAL_ERROR;
}
HAL_StatusTypeDef HAL_FLASH_Lock(void)
{
    f3_locks++;
    unlocked = false;
    return HAL_OK;
}
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *erase, uint32_t *error)
{
    CHECK(erase && error && erase->TypeErase == FLASH_TYPEERASE_PAGES &&
          erase->PageAddress == f3_address && erase->NbPages == 1);
    f3_erases++;
    if (!unlocked || !f3_erase_ok)
    {
        *error = f3_address;
        return HAL_ERROR;
    }
    memset((void *)f3_address, 0xff, FLASH_PAGE_SIZE);
    *error = 0xffffffff;
    return HAL_OK;
}
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t type, uint32_t address, uint64_t value)
{
    CHECK(unlocked && type == FLASH_TYPEPROGRAM_HALFWORD && value <= 65535);
    uintptr_t offset = address - f3_address;
    CHECK(!(offset & 1) && offset + 2 <= hal.nvs.size && offset == f3_programs * 2);
    f3_programs++;
    if (f3_programs == f3_fail_program)
        return HAL_ERROR;
    uint16_t half = value;
    memcpy((void *)(uintptr_t)address, &half, 2);
    return HAL_OK;
}
void f3_check_copy(void)
{
    CHECK(!memcmp((void *)f3_address, f3_source, hal.nvs.size));
    uint8_t dest[2052];
    memset(dest, 0x5a, sizeof(dest));
    CHECK(memcpy_from_flash(dest) && !memcmp(dest, f3_source, hal.nvs.size) &&
          dest[hal.nvs.size] == 0x5a);
    CHECK(*(uint8_t *)(f3_address + hal.nvs.size) == 255);
    CHECK(f3_unlocks == 1 && f3_erases == 1 && f3_locks == 1 && f3_programs == hal.nvs.size / 2 &&
          !unlocked);
}
