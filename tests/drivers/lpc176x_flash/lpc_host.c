#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#undef NEAR
#else
#include <sys/mman.h>
#endif
#include "lpc_host.h"
_Static_assert(sizeof(void *) == 4, "LPC176x fixture requires a32-bit host target");
grbl_hal_t hal;
uint32_t lpc_source[1024];
unsigned lpc_stage, lpc_fail_at, lpc_prepares, lpc_erases, lpc_copies, lpc_disables, lpc_enables,
    lpc_copied;
bool lpc_irqs_disabled;
static bool prepared;
void lpc_prepare(unsigned size)
{
    CHECK(size == 1024 || size == 2048 || size == 4096);
    hal.nvs.size = size;
    // Dedicated process-local flash mapping; never replace an existing mapping.
    static void *region;
    if (!region)
    {
#ifdef _WIN32
        region = VirtualAlloc((void *)0x70000, 65536, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
        region = mmap((void *)0x70000, 65536, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
#endif
        CHECK(region == (void *)0x70000);
    }
    memset((void *)LPC_FLASH_ADDRESS, 0, 4096);
    for (unsigned i = 0; i < 1024; i++)
        lpc_source[i] = 0x12340000 + i;
    lpc_stage = lpc_fail_at = lpc_prepares = lpc_erases = lpc_copies = lpc_disables = lpc_enables =
        lpc_copied = 0;
    lpc_irqs_disabled = prepared = false;
}
void __disable_irq(void)
{
    CHECK(!lpc_irqs_disabled);
    lpc_irqs_disabled = true;
    lpc_disables++;
}
void __enable_irq(void)
{
    CHECK(lpc_irqs_disabled);
    lpc_irqs_disabled = false;
    lpc_enables++;
}
uint8_t Chip_IAP_PreSectorForReadWrite(uint32_t first, uint32_t last)
{
    CHECK(lpc_irqs_disabled && first == 29 && last == 29);
    lpc_prepares++;
    lpc_stage++;
    prepared = lpc_fail_at != lpc_stage;
    return prepared ? IAP_CMD_SUCCESS : IAP_BUSY;
}
uint8_t Chip_IAP_EraseSector(uint32_t first, uint32_t last)
{
    CHECK(lpc_irqs_disabled && first == 29 && last == 29);
    lpc_erases++;
    lpc_stage++;
    bool ready = prepared;
    prepared = false;
    if (lpc_fail_at == lpc_stage)
        return IAP_BUSY;
    if (!ready)
        return IAP_SECTOR_NOT_PREPARED;
    memset((void *)LPC_FLASH_ADDRESS, 0xff, 4096);
    return IAP_CMD_SUCCESS;
}
uint8_t Chip_IAP_CopyRamToFlash(uint32_t address, uint32_t *source, uint32_t size)
{
    CHECK(lpc_irqs_disabled && address == LPC_FLASH_ADDRESS && source == lpc_source);
    CHECK(size == 1024 || size == 4096);
    lpc_copies++;
    lpc_stage++;
    bool ready = prepared;
    prepared = false;
    if (lpc_fail_at == lpc_stage)
        return IAP_BUSY;
    if (!ready)
        return IAP_SECTOR_NOT_PREPARED;
    for (unsigned i = 0; i < size; i++)
        if (((uint8_t *)LPC_FLASH_ADDRESS)[i] != 0xff)
            return IAP_SECTOR_NOT_BLANK;
    memcpy((void *)LPC_FLASH_ADDRESS, source, size);
    lpc_copied = size;
    return IAP_CMD_SUCCESS;
}
void lpc_check_copy(void)
{
    CHECK(!memcmp((void *)LPC_FLASH_ADDRESS, lpc_source, hal.nvs.size));
    uint8_t dest[4100];
    memset(dest, 0x5a, sizeof(dest));
    CHECK(memcpy_from_flash(dest));
    CHECK(!memcmp(dest, lpc_source, hal.nvs.size) && dest[hal.nvs.size] == 0x5a);
    CHECK(lpc_disables == 1 && lpc_enables == 1 && !lpc_irqs_disabled && lpc_prepares == 2 &&
          lpc_erases == 1 && lpc_copies == 1);
}
