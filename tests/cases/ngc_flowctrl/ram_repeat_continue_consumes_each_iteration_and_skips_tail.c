#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_root_protocol("#100=0\n#101=0\nO10REPEAT[3]\n#100=[#100+1]\nO10CONTINUE\n#101=99\nO10ENDREPEAT\n#102=7\n");
    NEAR(ram_flow_parameter(100), 3);
    NEAR(ram_flow_parameter(101), 0);
    NEAR(ram_flow_parameter(102), 7);
    return EXIT_SUCCESS;
}
