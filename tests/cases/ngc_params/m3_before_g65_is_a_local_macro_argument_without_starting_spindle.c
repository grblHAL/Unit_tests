#include "support/macro_m_argument_host.h"
int main(void)
{
    prepare_macro_m_argument();
    CHECK(macro_block("M3G65P100X2") == Status_OK);
    CHECK(macro_calls == 1 && called_macro == 100 && macro_scope == 1);
    CHECK(macro_words.m);
    NEAR(macro_m_argument, 3);
    NEAR(macro_x, 2);
    CHECK(!gc_spindle_get(0)->state.on);
    CHECK(plan_get_current_block() == NULL);
    float parent;
    CHECK(ngc_param_get(13, &parent));
    NEAR(parent, 99);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
