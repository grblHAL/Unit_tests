#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    sys.flags.probe_succeeded = true;
    sys.probe_position[X_AXIS] = 80;
    sys.probe_position[Y_AXIS] = 160;
    sys.probe_position[Z_AXIS] = 240;
    CHECK(system_command("$TLR") == Status_OK);
    CHECK(sys.tlo_reference_set.mask == Z_AXIS_BIT);
    CHECK(memcmp(sys.tlo_reference, sys.probe_position, sizeof(sys.probe_position)) == 0);
    return EXIT_SUCCESS;
}
