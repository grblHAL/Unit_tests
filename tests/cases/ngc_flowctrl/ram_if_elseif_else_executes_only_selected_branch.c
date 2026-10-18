#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_root_protocol("#100=0\nO10IF[0]\n#100=99\nO10ELSEIF[1]\n#100=7\nO10ELSE\n#100=88\nO10ENDIF\n#101=3\n");
    NEAR(ram_flow_parameter(100), 7);
    NEAR(ram_flow_parameter(101), 3);
    return EXIT_SUCCESS;
}
