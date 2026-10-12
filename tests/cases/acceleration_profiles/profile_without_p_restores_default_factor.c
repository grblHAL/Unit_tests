#include "support/protocol_host.h"
#include "check.h"

int main(void)
{
    prepare_protocol(); char reduced[] = "G187P5", reset[] = "G187";
    CHECK(gc_execute_block(reduced) == Status_OK); NEAR(gc_state.modal.acceleration_factor, 0.2f);
    CHECK(gc_execute_block(reset) == Status_OK); NEAR(gc_state.modal.acceleration_factor, 1);
    return EXIT_SUCCESS;
}
