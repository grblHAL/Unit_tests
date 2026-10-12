#include "support/protocol_host.h"
#include "check.h"

int main(void)
{
    prepare_protocol(); char selected[] = "G187P2", invalid[] = "G187P0";
    CHECK(gc_execute_block(selected) == Status_OK);
    CHECK(gc_execute_block(invalid) == Status_GcodeValueOutOfRange);
    NEAR(gc_state.modal.acceleration_factor, 0.8f);
    return EXIT_SUCCESS;
}
