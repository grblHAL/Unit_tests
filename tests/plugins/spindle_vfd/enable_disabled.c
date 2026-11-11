#include "enable_host.h"

int main(void)
{
    enable_prepare_ports(false);
    vfd_prepare(true);
    vfd_start();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){0}, 0);
    CHECK(vfd_requests == 4 && !vfd_warnings && !enable_writes[3]);
    enable_expect_claim(false);
    uint8_t port = 3;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "Still available"));
    return 0;
}
