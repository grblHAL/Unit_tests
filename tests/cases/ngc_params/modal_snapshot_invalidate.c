#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    gc_override_values_t overrides = {0};
    CHECK(ngc_modal_state_get() == NULL);
    CHECK(ngc_modal_state_save(&gc_state.modal, &overrides, 1, false));
    ngc_modal_state_invalidate();
    CHECK(ngc_modal_state_get() == NULL);
    ngc_modal_state_invalidate();
    CHECK(ngc_modal_state_get() == NULL);
    return EXIT_SUCCESS;
}
