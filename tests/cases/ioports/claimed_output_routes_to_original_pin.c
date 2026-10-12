#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    uint8_t port = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "Fixture output") != NULL);
    CHECK(ioport_digital_out(port, 1));
    CHECK(output_calls == 1);
    CHECK(physical_output == 0 && output_value);
    return EXIT_SUCCESS;
}
