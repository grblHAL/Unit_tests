#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    status_code_t result = canned_block("G89Z-1R0P0.1F100");
    if(result == Status_GcodeUnsupportedCommand) {
        CHECK(plan_get_current_block() == NULL);
        CHECK(axis_pulses[Z_AXIS] == 0);
        CHECK(physical_position[Z_AXIS] == 0);
        return EXIT_SUCCESS;
    }
    CHECK(result == Status_OK);
    CHECK(protocol_buffer_synchronize());
    fprintf(stderr, "G89: accepted status=%u, Z pulses=%u; expected 160 for drilling and retract\n", (unsigned)result, axis_pulses[Z_AXIS]);
    CHECK(axis_pulses[Z_AXIS] == 160);
    CHECK(physical_position[Z_AXIS] == 0);
    CHECK(sys.position[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
