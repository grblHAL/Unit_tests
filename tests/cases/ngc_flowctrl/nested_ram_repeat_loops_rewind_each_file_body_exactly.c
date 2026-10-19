#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_root_protocol("#100=0\nO10REPEAT[2]\nO20REPEAT[3]\n#100=[#100+1]\nO20ENDREPEAT\nO10ENDREPEAT\n#101=7\n");
    NEAR(ram_flow_parameter(100), 6);
    NEAR(ram_flow_parameter(101), 7);
    return EXIT_SUCCESS;
}
