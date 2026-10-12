#include "support/macro_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_macro_parser();
    CHECK(macro_block("G65P100X12.5Y-3Z2") == Status_OK);
    CHECK(macro_calls == 1);
    NEAR(macro_x, 12.5f);
    NEAR(macro_y, -3);
    NEAR(macro_z, 2);
    CHECK(macro_words.x && macro_words.y && macro_words.z);
    CHECK(macro_scope == 1);
    CHECK(ngc_call_level() == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(gc_state.position[axis], 0);
    return EXIT_SUCCESS;
}
