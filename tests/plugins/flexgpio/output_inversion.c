#include "flex_host.h"
int main(void)
{
    flex_start();
    xbar_t pin = flex_pin(Port_Output, 0);
    gpio_out_config_t cfg = {.inverted = true};
    CHECK(pin.config(&pin, &cfg, true));
    CHECK(saved == 1);
    bank.digital_out(0, true);
    CHECK((last_packet[2] & 0x80) == 0);
    bank.digital_out(0, false);
    CHECK(last_packet[2] & 0x80);
    return 0;
}
