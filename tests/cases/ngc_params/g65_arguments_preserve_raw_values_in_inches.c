#include "support/macro_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_macro_parser();
    CHECK(macro_block("G20") == Status_OK);
    CHECK(macro_block("G65P100X2.5") == Status_OK);
    CHECK(macro_calls == 1);
    NEAR(macro_x, 2.5f);
    CHECK(gc_state.modal.units_imperial);
    NEAR(gc_state.position[X_AXIS], 0);
    return EXIT_SUCCESS;
}
