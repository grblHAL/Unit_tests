#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    gc_override_values_t overrides = {0};
    int context;
    CHECK(ngc_modal_state_save(&gc_state.modal, &overrides, 11, false));
    CHECK(ngc_call_push(&context));
    CHECK(ngc_modal_state_get() == NULL);
    CHECK(ngc_modal_state_save(&gc_state.modal, &overrides, 22, false));
    NEAR(ngc_modal_state_get()->modal.feed_rate, 22);
    (void)ngc_call_pop();
    NEAR(ngc_modal_state_get()->modal.feed_rate, 11);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
