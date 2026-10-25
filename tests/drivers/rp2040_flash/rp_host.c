#include "rp_host.h"
grbl_hal_t hal;
uint8_t rp_memory[2016 * 1024 + 4096];
unsigned rp_erases, rp_programs, rp_irq_phase;
size_t rp_program_size;
bool rp_corrupt;
void rp_prepare(size_t size)
{
    CHECK(size <= 4096);
    memset(rp_memory, 255, sizeof(rp_memory));
    hal.nvs.size = size;
}
void __disable_irq(void)
{
    CHECK(rp_irq_phase == 0);
    rp_irq_phase = 1;
}
void flash_range_erase(uint32_t offset, size_t size)
{
    CHECK(rp_irq_phase == 1 && offset == RP_OFFSET && size == FLASH_SECTOR_SIZE);
    rp_irq_phase = 2;
    rp_erases++;
    memset(rp_memory + offset, 255, size);
}
void flash_range_program(uint32_t offset, const uint8_t *data, size_t size)
{
    CHECK(rp_irq_phase == 2 && offset == RP_OFFSET && size <= 4096 && size % FLASH_PAGE_SIZE == 0);
    rp_irq_phase = 3;
    rp_programs++;
    rp_program_size = size;
    memcpy(rp_memory + offset, data, size);
    if (rp_corrupt)
        rp_memory[offset] ^= 1;
}
void __enable_irq(void)
{
    CHECK(rp_irq_phase == 3);
    rp_irq_phase = 0;
}
