#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    sys.tlo_reference_set.mask = Z_AXIS_BIT;
    CHECK(system_command("$TLR") == Status_OK);
    CHECK(sys.tlo_reference_set.mask == 0);
    return EXIT_SUCCESS;
}
