#include "spi_host.h"
grbl_hal_t hal;
io_digital_t bank;
bool start_ok = true, select_ok = true;
unsigned starts, selections, deselections, transfers, registrations;
uint32_t shifted;
static bool selected;
static void enumerate(bool low_level, pin_info_ptr callback, void *data)
{
    (void)low_level;
    xbar_t pin = {.group = PinGroup_AuxOutput, .function = Output_Aux1};
    callback(&pin, data);
}
void start_hc595(void)
{
    void hc595_init(void);
    hal.enumerate_pins = enumerate;
    hc595_init();
}
static void check_slave(spi_slave_t *slave)
{
    CHECK(slave && slave->cs_pin == 7 && slave->cs_port == NULL);
#ifdef HC595_FCLK
    CHECK(slave->f_clock == HC595_FCLK);
#else
    CHECK(slave->f_clock == 4000000);
#endif
}
spi_cap_t spi_start(spi_slave_t *slave)
{
    check_slave(slave);
    starts++;
    return (spi_cap_t){.started = start_ok};
}
bool spi_select(spi_slave_t *slave)
{
    check_slave(slave);
    CHECK(!selected);
    selections++;
    selected = select_ok;
    return selected;
}
bool spi_deselect(spi_slave_t *slave)
{
    check_slave(slave);
    CHECK(selected);
    selected = false;
    deselections++;
    return true;
}
uint8_t spi_put_byte(uint8_t byte)
{
    CHECK(HC595_ENABLE == 1 && selected);
    shifted = byte;
    transfers++;
    return 0;
}
bool spi_write(uint8_t *data, uint16_t size)
{
    CHECK(HC595_ENABLE > 1 && size == HC595_ENABLE && selected);
    shifted = 0;
    for (unsigned i = 0; i < size; i++)
        shifted = (shifted << 8) | data[i];
    transfers++;
    return true;
}
bool ioports_add_digital(io_digital_t *ports)
{
    CHECK(!registrations && ports->ports->external);
    CHECK(ports->ports->out.n_ports == HC595_ENABLE * 8 && ports->ports->in.n_ports == 0);
    bank = *ports;
    registrations++;
    return true;
}
void ioport_save_output_settings(xbar_t *pin, gpio_out_config_t *config)
{
    (void)pin;
    (void)config;
    CHECK(false);
}
