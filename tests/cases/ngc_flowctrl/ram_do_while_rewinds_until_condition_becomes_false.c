#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_root_protocol("#100=0\nO10DO\n#100=[#100+1]\nO10WHILE[#100LT3]\n#101=7\n");
    NEAR(ram_flow_parameter(100), 3);
    NEAR(ram_flow_parameter(101), 7);
    return EXIT_SUCCESS;
}
