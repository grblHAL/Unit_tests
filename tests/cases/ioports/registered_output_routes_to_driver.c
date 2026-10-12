#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    CHECK(ioport_digital_out(1, 1));
    CHECK(output_calls == 1);
    CHECK(physical_output == 1 && output_value);
    CHECK(ioport_digital_out(0, 0));
    CHECK(output_calls == 2);
    CHECK(physical_output == 0 && !output_value);
    return EXIT_SUCCESS;
}
