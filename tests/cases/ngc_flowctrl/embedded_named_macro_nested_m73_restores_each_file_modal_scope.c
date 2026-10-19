#define NAMED_MACRO_BODY "M73\nG20G91G18F10\nO<inner>CALL[4]\n#102=#<_metric>\n"
#define INNER_MACRO_BODY "M73\nG21G90G19F22\n#103=#<_metric>\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("G21G90G17F120\nO<fixture>CALL[3]\n#100=#<_metric>\n#101=#<_absolute>\n");
    NEAR(ram_flow_parameter(100), 1);
    NEAR(ram_flow_parameter(101), 1);
    NEAR(ram_flow_parameter(102), 0);
    NEAR(ram_flow_parameter(103), 1);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    NEAR(gc_state.feed_rate, 120);
    CHECK(ngc_modal_state_get() == NULL);
    return EXIT_SUCCESS;
}
