#include "support/lathe_cycle_capture_host.h"
int main(void)
{
    prepare_lathe_capture();
    CHECK(css_block("G17G71X10Z20Q7F100") == Status_GcodeIllegalPlane);
    CHECK(lathe_cycle_calls == 0);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    return EXIT_SUCCESS;
}
