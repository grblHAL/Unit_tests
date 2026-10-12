#include "support/probe_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_probe_motion();
    away_contact = true;
    char block[] = "G38.4X1F100";
    CHECK(gc_execute_block(block) == Status_OK);
    CHECK(sys.flags.probe_succeeded);
    CHECK(sys.probe_position[X_AXIS] == 40);
    CHECK(completed_calls == 1);
    return EXIT_SUCCESS;
}
