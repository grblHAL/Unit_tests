#include "support/protocol_host.h"
#include "check.h"

int main(void)
{
    prepare_protocol(); char selected[] = "G187P5";
    CHECK(gc_execute_block(selected) == Status_OK); gc_init(false);
    NEAR(gc_state.modal.acceleration_factor, 1);
    return EXIT_SUCCESS;
}
