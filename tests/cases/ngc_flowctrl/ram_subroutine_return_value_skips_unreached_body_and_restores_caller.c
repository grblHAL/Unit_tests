#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_root_protocol("#1=99\n#100=0\nO10SUB\n#100=#1\nO10RETURN[7]\n#100=88\nO10ENDSUB\nO10CALL[12]\n#101=#<_value>\n#102=#<_value_returned>\n");
    NEAR(ram_flow_parameter(100), 12);
    NEAR(ram_flow_parameter(1), 99);
    NEAR(ram_flow_parameter(101), 7);
    NEAR(ram_flow_parameter(102), 1);
    return EXIT_SUCCESS;
}
