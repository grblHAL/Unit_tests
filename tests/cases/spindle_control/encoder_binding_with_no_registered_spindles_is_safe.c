#include "support/spindle_encoder_binding_host.h"
int main(void)
{
    engine_prepare();
    CHECK(spindle_get_count() == 0);
    spindle_bind_encoder(&binding_encoder);
    spindle_bind_encoder(NULL);
    CHECK(spindle_get_count() == 0);
    CHECK(native_reads == 0 && external_reads == 0);
    CHECK(native_resets == 0 && external_resets == 0);
    return EXIT_SUCCESS;
}
