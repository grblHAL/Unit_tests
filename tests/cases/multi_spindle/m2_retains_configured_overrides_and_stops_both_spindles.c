#include "support/multi_spindle_program_end_host.h"
int main(void)
{
    prepare_multi_spindle_program_end(false);
    CHECK(spindle_program_block("M2") == Status_OK);
    check_multi_spindle_program_end(false, ProgramFlow_CompletedM2);
    return EXIT_SUCCESS;
}
