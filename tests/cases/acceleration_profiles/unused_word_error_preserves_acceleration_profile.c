#include "support/protocol_host.h"
#include "check.h"

int main(void)
{
    prepare_protocol(); NEAR(gc_state.modal.acceleration_factor, 1);
    char invalid[] = "G187P5R1"; CHECK(gc_execute_block(invalid) == Status_GcodeUnusedWords);
    NEAR(gc_state.modal.acceleration_factor, 1);
    return EXIT_SUCCESS;
}
