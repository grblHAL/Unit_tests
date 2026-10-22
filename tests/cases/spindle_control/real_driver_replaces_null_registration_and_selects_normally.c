#include "support/spindle_encoder_binding_host.h"
#include <string.h>

int main(void)
{
    engine_prepare();
    sys.cold_start = true;
    CHECK(spindle_add_null() == 0);
    CHECK(spindle_get_hal(0, SpindleHAL_Raw)->type == SpindleType_Null);

    register_binding_spindle(false);
    CHECK(spindle_get_count() == 1);
    CHECK(strcmp(spindle_get_name(0), "encoder host") == 0);
    CHECK(spindle_select(0));
    spindle_ptrs_t *active = spindle_get(0);
    CHECK(active != NULL && active->type == SpindleType_Basic);
    CHECK(active->set_state == binding_spindle_write);
    CHECK(active->get_state == binding_spindle_read);
    CHECK(!active->get_state(active).on);
    CHECK(spindle_get_default() == 0 && spindle_is_enabled(-1));
    CHECK(spindle_select(0));
    CHECK(spindle_get_count() == 1);
    CHECK(spindle_get(0)->set_state == binding_spindle_write);
    return EXIT_SUCCESS;
}
