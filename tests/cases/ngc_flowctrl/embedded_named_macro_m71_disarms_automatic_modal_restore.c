#define NAMED_MACRO_BODY "M73\nM71\nG20G91G18F10\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("G21G90G17F120\nO<fixture>CALL\n#100=#<_metric>\n#101=#<_absolute>\n");
    NEAR(ram_flow_parameter(100), 0);
    NEAR(ram_flow_parameter(101), 0);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    NEAR(gc_state.feed_rate, 254);
    CHECK(ngc_modal_state_get() == NULL);
    return EXIT_SUCCESS;
}
