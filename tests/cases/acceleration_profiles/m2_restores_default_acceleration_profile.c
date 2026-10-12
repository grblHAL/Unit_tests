#include "support/program_end_host.h"
#include "check.h"

int main(void)
{
    prepare_program_end(false); CHECK(program_block("G187P5") == Status_OK);
    CHECK(program_block("M2") == Status_OK); NEAR(gc_state.modal.acceleration_factor, 1);
    CHECK(program_complete_calls == 1);
    return EXIT_SUCCESS;
}
