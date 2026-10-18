#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_root_protocol("#100=0\nO10REPEAT[0]\nG65P10A5\n#100=99\nO10ENDREPEAT\nO20WHILE[0]\nG65P20A7\n#100=88\nO20ENDWHILE\n#101=7\n");
    NEAR(ram_flow_parameter(100), 0);
    NEAR(ram_flow_parameter(101), 7);
    return EXIT_SUCCESS;
}
