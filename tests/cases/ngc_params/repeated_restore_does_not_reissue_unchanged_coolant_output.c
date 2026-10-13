#include "support/program_end_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_program_end(false);
    hal.coolant_cap.flood = true;
    CHECK(program_block("M8") == Status_OK);
    CHECK(program_block("M70") == Status_OK);
    CHECK(program_block("M9") == Status_OK);
    CHECK(program_block("M72") == Status_OK);
    unsigned calls = coolant_calls;
    CHECK(actual_coolant.flood);
    CHECK(program_block("M72") == Status_OK);
    CHECK(coolant_calls == calls);
    CHECK(actual_coolant.flood && gc_state.modal.coolant.flood);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
