#include "support/incoming_macro_host.h"
int main(void)
{
    prepare_incoming_macro();
    CHECK(incoming_block("G65P100A1B2") == Status_OK);
    CHECK(macro_calls == 1 && incoming_called_macro == 100);
    NEAR(incoming_arguments[0], 1); NEAR(incoming_arguments[1], 2);
    CHECK(incoming_block("G65P101A10B20") == Status_OK);
    CHECK(macro_calls == 2 && incoming_called_macro == 101);
    NEAR(incoming_arguments[0], 10); NEAR(incoming_arguments[1], 20);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
