#include "support/program_end_host.h"
#include "check.h"

int main(void)
{
    prepare_program_end(false);
    hal.coolant_cap.flood = true;
    CHECK(program_block("M8") == Status_OK);
    CHECK(actual_coolant.flood);
    CHECK(program_block("M2") == Status_OK);
    CHECK(!actual_coolant.flood);
    CHECK(!gc_state.modal.coolant.flood);
    CHECK(coolant_calls == 2);
    return EXIT_SUCCESS;
}
