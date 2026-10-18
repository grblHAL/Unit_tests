#define NAMED_MACRO_BODY "#100=#1\nO<fixture>RETURN[7]\n#100=88\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("#1=99\nO<fixture>CALL[12]\n#101=#<_value>\n#102=#<_value_returned>\n#103=#1\n");
    NEAR(ram_flow_parameter(100), 12);
    NEAR(ram_flow_parameter(101), 7);
    NEAR(ram_flow_parameter(102), 1);
    NEAR(ram_flow_parameter(103), 99);
    return EXIT_SUCCESS;
}
