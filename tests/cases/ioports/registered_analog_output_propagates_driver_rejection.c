#include "support/ioports_analog_host.h"
#include "check.h"

int main(void)
{
    prepare_analog_ports();
    analog_output_result = false;
    CHECK(!ioport_analog_out(1, 2.5f));
    CHECK(analog_output_calls == 1 && analog_output_pin == 1);
    NEAR(analog_output_value, 2.5f);
    return EXIT_SUCCESS;
}
