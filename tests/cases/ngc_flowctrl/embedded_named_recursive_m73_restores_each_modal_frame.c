#define NAMED_MACRO_BODY "M73\n#100=[#100+1]\nO10IF[#1GT0]\nG20G91G18F10\nO<fixture>CALL[#1-1]\nO10ELSE\nG21G90G19F22\nO10ENDIF\n#101=[#101+#<_metric>]\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("#1=99\n#100=0\n#101=0\nG21G90G17F120\nO<fixture>CALL[3]\n#102=#<_metric>\n#103=#<_absolute>\n");
    NEAR(ram_flow_parameter(100), 4);
    NEAR(ram_flow_parameter(101), 1);
    NEAR(ram_flow_parameter(102), 1);
    NEAR(ram_flow_parameter(103), 1);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    NEAR(gc_state.feed_rate, 120);
    CHECK(ngc_modal_state_get() == NULL);
    return EXIT_SUCCESS;
}
