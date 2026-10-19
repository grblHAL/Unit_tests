#define NAMED_MACRO_BODY "#100=[#100+1]\n#101=#<_call_level>\nO10IF[#<_call_level>LT3]\nO<fixture>CALL\nO10ENDIF\n#102=[#102+#<_call_level>]\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("#100=0\n#102=0\nO<fixture>CALL\n#103=#<_call_level>\n");
    NEAR(ram_flow_parameter(100), 3);
    NEAR(ram_flow_parameter(101), 3);
    NEAR(ram_flow_parameter(102), 6);
    NEAR(ram_flow_parameter(103), 0);
    return EXIT_SUCCESS;
}
