#include "support/ioports_analog_host.h"
#include "check.h"

int main(void)
{
    prepare_analog_ports();
    uint8_t port = 0;
    CHECK(ioport_claim(Port_Analog, Port_Output, &port, "Servo") != NULL);
    pwm_config_t config = {.freq_hz = 50};
    CHECK(ioport_analog_out_config(port, &config));
    CHECK(pwm_config_calls == 1);
    CHECK(configured_pwm_pin == &analog_pins[Port_Output][0]);
    return EXIT_SUCCESS;
}
