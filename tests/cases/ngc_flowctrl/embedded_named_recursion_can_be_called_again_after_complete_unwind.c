#define NAMED_MACRO_BODY "#100=[#100+1]\nO10IF[#1GT0]\nO<fixture>CALL[#1-1]\nO10ENDIF\n#101=[#101+#1]\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("#1=99\n#100=0\n#101=0\nO<fixture>CALL[3]\nO<fixture>CALL[2]\n#102=#1\n");
    NEAR(ram_flow_parameter(100), 7);
    NEAR(ram_flow_parameter(101), 9);
    NEAR(ram_flow_parameter(102), 99);
    return EXIT_SUCCESS;
}
