#include "support/spindle_encoder_binding_host.h"
int main(void)
{
    prepare_encoder_binding(true,true);
    spindle_bind_encoder(&binding_encoder);
    spindle_bind_encoder(NULL);
    spindle_ptrs_t *active = spindle_get(0);
    CHECK(active->get_data(SpindleData_RPM) == &native_feedback);
    active->reset_data();
    CHECK(native_reads == 1 && native_resets == 1 && external_resets == 0);
    CHECK(!active->cap.at_speed);
    return EXIT_SUCCESS;
}
