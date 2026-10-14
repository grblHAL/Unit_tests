#include "support/spindle_encoder_binding_host.h"
int main(void)
{
    prepare_encoder_binding(false,true);
    spindle_bind_encoder(&binding_encoder);
    spindle_ptrs_t *active = spindle_get(0);
    CHECK(active->get_data(SpindleData_RPM) == &external_feedback);
    CHECK(!active->cap.at_speed);
    return EXIT_SUCCESS;
}
