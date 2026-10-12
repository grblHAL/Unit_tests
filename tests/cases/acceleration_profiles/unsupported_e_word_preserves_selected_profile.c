#include "support/protocol_host.h"
#include "check.h"

int main(void)
{
    prepare_protocol(); char selected[] = "G187P3", invalid[] = "G187P2E1";
    CHECK(gc_execute_block(selected) == Status_OK);
    CHECK(gc_execute_block(invalid) == Status_GcodeUnsupportedCommand);
    NEAR(gc_state.modal.acceleration_factor, 0.6f);
    return EXIT_SUCCESS;
}
