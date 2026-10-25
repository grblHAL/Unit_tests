#include "coolant_host.h"
int main(void)
{
    coolant_prepare(true);
    uint8_t port = 0;
    CHECK(ioport_claim(Port_Digital, Port_Input, &port, "Other plugin"));
    coolant_load();
    hal.coolant.set_state((coolant_state_t){.flood = On});
    CHECK(coolant_output.flood && !coolant_irqs);
    return 0;
}
