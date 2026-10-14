#include "support/spindle_encoder_binding_host.h"
int main(void)
{
    prepare_encoder_binding(true,true);
    spindle_bind_encoder(&binding_encoder);
    const spindle_ptrs_t *raw = spindle_get_hal(0,SpindleHAL_Raw);
    CHECK(raw->get_data == native_encoder_read && raw->reset_data == native_encoder_reset);
    CHECK(!raw->cap.at_speed);
    CHECK(spindle_get(0)->get_data == external_encoder_read);
    return EXIT_SUCCESS;
}
