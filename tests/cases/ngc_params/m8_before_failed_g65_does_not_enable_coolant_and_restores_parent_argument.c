#include "support/macro_m_argument_host.h"
static unsigned macro_coolant_calls;
static void record_macro_coolant(coolant_state_t state)
{
    (void)state;
    macro_coolant_calls++;
}
int main(void)
{
    prepare_macro_m_argument();
    hal.coolant.set_state = record_macro_coolant;
    macro_result = Status_InvalidStatement;
    CHECK(macro_block("M8G65P100") == Status_InvalidStatement);
    CHECK(macro_calls == 1 && macro_words.m);
    NEAR(macro_m_argument, 8);
    CHECK(macro_coolant_calls == 0 && gc_state.modal.coolant.value == 0);
    float parent;
    CHECK(ngc_param_get(13, &parent));
    NEAR(parent, 99);
    CHECK(ngc_call_level() == 0 && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
