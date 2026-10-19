#define NAMED_MACRO_BODY "#100=#<_call_level>\nO<fixture>RETURN[7]\n#100=99\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("#101=#<_call_level>\nO<fixture>CALL\n#102=#<_call_level>\n#103=#<_value>\n");
    NEAR(ram_flow_parameter(100), 1);
    NEAR(ram_flow_parameter(101), 0);
    NEAR(ram_flow_parameter(102), 0);
    NEAR(ram_flow_parameter(103), 7);
    return EXIT_SUCCESS;
}
