#include "support/program_end_host.h"
static void check_completed(program_flow_t flow, bool check_mode)
{
    CHECK(!check_mode && flow == ProgramFlow_CompletedM30);
    CHECK(gc_state.modal.g5x_offset.id == CoordinateSystem_G54);
    CHECK(actual_coolant.mask == 0 && gc_state.modal.coolant.mask == 0);
    program_completed(flow, check_mode);
}
int main(void)
{
    prepare_program_end(false);
    hal.coolant_cap.flood = true;
    CHECK(program_block("G55M8") == Status_OK);
    CHECK(actual_coolant.flood);
    grbl.on_program_completed = check_completed;
    CHECK(program_block("M30") == Status_OK);
    CHECK(program_complete_calls == 1);
    return EXIT_SUCCESS;
}
