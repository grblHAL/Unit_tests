#include "support/spindle_encoder_binding_host.h"
int main(void)
{
    prepare_encoder_binding(true,false);
    spindle_bind_encoder(&binding_encoder);
    CHECK(spindle_select(0));
    spindle_ptrs_t *active = spindle_get(0);
    CHECK(active->get_data(SpindleData_RPM) == &external_feedback);
    active->reset_data();
    CHECK(external_resets == 1);
    return EXIT_SUCCESS;
}
