#include "support/probe_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_motion();
    away_contact = true;
    contact_steps = 1000;
    char block[] = "G38.5X1F100";
    CHECK(gc_execute_block(block) == Status_OK);
    CHECK(!sys.flags.probe_succeeded);
    CHECK(sys.probe_position[X_AXIS] == 80);
    NEAR(gc_state.position[X_AXIS], 1);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
