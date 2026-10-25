#include "tmc_host.h"
static uint32_t idle_status;
void tmc_spi20_prepare(void) { idle_status = (TMC2660_drvstatus3_t){.stst = 1}.value; }
TMC_spi20_datagram_t tmc_spi20_write(trinamic_motor_t driver, TMC_spi20_datagram_t *packet)
{
    CHECK(driver.id < 3 && packet && packet->value < (1UL << 20));
    tmc_writes++;
    tmc_reads++;
    if (tmc_bus_ok)
    {
        unsigned address = (packet->value >> 17) & 7;
        tmc_registers[driver.id][address] = packet->value & 0x1ffff;
    }
    return (TMC_spi20_datagram_t){.value = tmc_bus_ok ? idle_status : 0xffffff};
}
TMC_spi20_datagram_t tmc_spi20_read(trinamic_motor_t driver, TMC_spi20_datagram_t *packet)
{
    return tmc_spi20_write(driver, packet);
}
