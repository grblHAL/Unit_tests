#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_root_protocol("#100=0\nO10REPEAT[5]\n#100=[#100+1]\nO20IF[#100EQ2]\nO10BREAK\nO20ENDIF\nO10ENDREPEAT\n#101=7\n");
    NEAR(ram_flow_parameter(100), 2);
    NEAR(ram_flow_parameter(101), 7);
    return EXIT_SUCCESS;
}
