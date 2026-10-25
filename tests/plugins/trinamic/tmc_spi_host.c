#include "tmc_host.h"
void tmc_spi_prepare(void)
{
    for (unsigned i = 0; i < 3; i++)
    {
#if TRINAMIC_ENABLE == 2130
        tmc_registers[i][TMC2130Reg_DRV_STATUS] = (TMC2130_drv_status_reg_t){.stst = 1}.value;
#elif TRINAMIC_ENABLE == 2240
        tmc_registers[i][TMC2240Reg_DRV_STATUS] = (TMC2240_drv_status_reg_t){.stst = 1}.value;
#elif TRINAMIC_ENABLE == 5160
        tmc_registers[i][TMC5160Reg_DRV_STATUS] = (TMC5160_drv_status_reg_t){.stst = 1}.value;
#endif
    }
}
TMC_spi_status_t tmc_spi_write(trinamic_motor_t driver, TMC_spi_datagram_t *packet)
{
    CHECK(driver.id < 3 && packet);
    tmc_writes++;
    if (tmc_bus_ok)
        tmc_registers[driver.id][packet->addr.idx] = packet->payload.value;
    return 0;
}
TMC_spi_status_t tmc_spi_read(trinamic_motor_t driver, TMC_spi_datagram_t *packet)
{
    CHECK(driver.id < 3 && packet);
    tmc_reads++;
    packet->payload.value = tmc_bus_ok ? tmc_registers[driver.id][packet->addr.idx] : UINT32_MAX;
    return 0;
}
