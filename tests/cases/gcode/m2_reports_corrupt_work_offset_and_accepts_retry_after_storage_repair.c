#include "support/program_end_storage_host.h"
int main(void)
{
    prepare_program_end(false);
    corrupt_end_coordinate(CoordinateSystem_G54);
    CHECK(program_block("M2") == Status_SettingReadFail);
    CHECK(program_complete_calls == 0);
    CHECK(gc_state.modal.program_flow == ProgramFlow_Running);
    CHECK(plan_get_current_block() == NULL);
    CHECK(program_block("M2") == Status_OK);
    CHECK(program_complete_calls == 1 && program_completion == ProgramFlow_CompletedM2);
    return EXIT_SUCCESS;
}
