#include "support/ioports_analog_host.h"
#include "check.h"

int main(void)
{
    prepare_analog_ports();
    CHECK(ioports_available(Port_Analog, Port_Input) == 2);
    CHECK(ioports_available(Port_Analog, Port_Output) == 2);
    CHECK(ioports_unclaimed(Port_Analog, Port_Input) == 2);
    CHECK(ioports_unclaimed(Port_Analog, Port_Output) == 2);
    return EXIT_SUCCESS;
}
