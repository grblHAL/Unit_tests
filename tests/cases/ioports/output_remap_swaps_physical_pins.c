#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    CHECK(ioport_remap(Port_Digital, Port_Output, 0, 1));
    CHECK(ioport_digital_out(0, 1));
    CHECK(physical_output == 1);
    CHECK(ioport_digital_out(1, 1));
    CHECK(physical_output == 0);
    CHECK(output_calls == 2);
    return EXIT_SUCCESS;
}
