#include "support/ioports_analog_host.h"
#include "check.h"

int main(void)
{
    prepare_analog_ports();
    uint8_t port = 0;
    CHECK(ioport_claim(Port_Analog, Port_Output, &port, "Servo") != NULL);
    CHECK(ioport_analog_out(port, 27.5f));
    CHECK(analog_output_calls == 1 && analog_output_pin == 0);
    NEAR(analog_output_value, 27.5f);
    CHECK(ioports_unclaimed(Port_Analog, Port_Output) == 1);
    return EXIT_SUCCESS;
}
