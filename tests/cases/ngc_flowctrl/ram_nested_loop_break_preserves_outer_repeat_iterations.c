#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_root_protocol("#100=0\n#101=0\nO10REPEAT[3]\n#100=[#100+1]\nO20REPEAT[5]\n#101=[#101+1]\nO20BREAK\nO20ENDREPEAT\nO10ENDREPEAT\n#102=7\n");
    NEAR(ram_flow_parameter(100), 3);
    NEAR(ram_flow_parameter(101), 3);
    NEAR(ram_flow_parameter(102), 7);
    return EXIT_SUCCESS;
}
