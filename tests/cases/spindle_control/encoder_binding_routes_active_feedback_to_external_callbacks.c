#include "support/spindle_encoder_binding_host.h"
int main(void)
{
    prepare_encoder_binding(true,true);
    spindle_bind_encoder(&binding_encoder);
    spindle_ptrs_t *active = spindle_get(0);
    CHECK(active != NULL);
    CHECK(active->get_data(SpindleData_RPM) == &external_feedback);
    NEAR(active->get_data(SpindleData_RPM)->rpm,1200);
    active->reset_data();
    CHECK(external_reads == 2 && external_resets == 1 && native_reads == 0);
    CHECK(active->cap.at_speed);
    NEAR(external_feedback.rpm,1200);
    return EXIT_SUCCESS;
}
