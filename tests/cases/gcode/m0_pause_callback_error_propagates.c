#include "support/program_end_host.h"
#include "check.h"

int main(void)
{
    prepare_program_end(false);
    program_pause_result = Status_InvalidStatement;
    CHECK(program_block("M0") == Status_InvalidStatement);
    CHECK(program_pause_calls == 1);
    CHECK(program_complete_calls == 0);
    CHECK(gc_state.modal.program_flow == ProgramFlow_Running);
    return EXIT_SUCCESS;
}
