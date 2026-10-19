#include "support/probe_motion_host.h"
#include "support/incoming_gcode_host.h"
int main(void)
{
    prepare_probe_motion();
    CHECK(incoming_block("G38.2X1F100") == Status_OK);
    CHECK(sys.probe_position[X_AXIS] == 40 && sys.flags.probe_succeeded);
    contact_steps = 120;
    CHECK(incoming_block("G38.3X2F100") == Status_OK);
    CHECK(sys.probe_position[X_AXIS] == 120 && sys.flags.probe_succeeded);
    away_contact = true; contact_steps = 160;
    CHECK(incoming_block("G38.4X3F100") == Status_OK);
    CHECK(sys.probe_position[X_AXIS] == 160 && sys.flags.probe_succeeded);
    contact_steps = 200;
    CHECK(incoming_block("G38.5X4F100") == Status_OK);
    CHECK(sys.probe_position[X_AXIS] == 200 && sys.flags.probe_succeeded);
    CHECK(completed_calls == 4 && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
