#include "support/program_end_host.h"
#include "check.h"

int main(void)
{
    prepare_program_end(true);
    CHECK(program_block("G20F2") == Status_OK);
    CHECK(program_block("M2") == Status_OK);
    CHECK(gc_state.modal.units_imperial);
    NEAR(gc_state.feed_rate, 50.8f);
    return EXIT_SUCCESS;
}
