#include "support/spindle_encoder_binding_host.h"
int main(void)
{
    prepare_encoder_binding(true,true);
    spindle_bind_encoder(&binding_encoder);
    CHECK(spindle_get(0)->get_data(SpindleData_RPM) == &external_feedback);
    settings.spindle.encoder_spindle = 9;
    spindle_bind_encoder(&binding_encoder);
    CHECK(spindle_get(0)->get_data(SpindleData_RPM) == &native_feedback);
    CHECK(native_reads == 1 && external_reads == 1);
    return EXIT_SUCCESS;
}
