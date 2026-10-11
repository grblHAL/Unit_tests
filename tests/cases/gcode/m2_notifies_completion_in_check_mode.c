#include "support/program_end_host.h"
#include "check.h"

int main(void)
{
    prepare_program_end(true);

    CHECK(program_block("M2") == Status_OK);
    CHECK(program_complete_calls == 1);
    CHECK(program_completion == ProgramFlow_CompletedM2);
    CHECK(program_completion_check_mode);
    return EXIT_SUCCESS;
}
