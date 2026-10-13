#include "support/program_end_host.h"
#include "ngc_params.h"

int main(void)
{
    prepare_program_end(false);
    hal.coolant_cap.flood = true;
    CHECK(program_block("M8") == Status_OK);
    CHECK(actual_coolant.flood);
    CHECK(program_block("M70") == Status_OK);
    CHECK(program_block("M9") == Status_OK);
    CHECK(!actual_coolant.flood);
    unsigned before = coolant_calls;
    CHECK(ngc_modal_state_restore());
    CHECK(gc_state.modal.coolant.flood && actual_coolant.flood);
    CHECK(coolant_calls == before + 1);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
