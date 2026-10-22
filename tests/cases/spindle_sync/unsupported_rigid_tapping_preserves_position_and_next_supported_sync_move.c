#include "support/spindle_sync_parser_host.h"
int main(void)
{
    prepare_sync_parser();
    CHECK(sync_parser_block("G33Z1K1") == Status_OK);
    CHECK(axis_pulses[Z_AXIS] == 80 && sys.position[Z_AXIS] == 80);
    status_code_t status = sync_parser_block("G33.1Z2K1");
    fprintf(stderr, "Native tapping stub: status=%u, parser Z=%g, physical steps=%ld\n",
            (unsigned)status, (double)gc_state.position[Z_AXIS], (long)physical_position[Z_AXIS]);
    CHECK(status == Status_GcodeUnsupportedCommand);
    NEAR(gc_state.position[Z_AXIS], 1);
    CHECK(physical_position[Z_AXIS] == 80 && sys.position[Z_AXIS] == 80);
    CHECK(axis_pulses[Z_AXIS] == 80 && plan_get_current_block() == NULL);
    CHECK(sync_parser_block("G33Z2K1") == Status_OK);
    CHECK(axis_pulses[Z_AXIS] == 160 && physical_position[Z_AXIS] == 160);
    CHECK(sys.position[Z_AXIS] == 160 && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
