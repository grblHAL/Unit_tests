#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_macro_protocol("#100=#<_call_level>\nG65P10A5\n#104=#<_call_level>\n",
        "#101=#<_call_level>\nG65P20A7\n#103=#<_call_level>\n",
        "#102=#<_call_level>\n");
    NEAR(ram_flow_parameter(100), 0);
    NEAR(ram_flow_parameter(101), 1);
    NEAR(ram_flow_parameter(102), 2);
    NEAR(ram_flow_parameter(103), 1);
    NEAR(ram_flow_parameter(104), 0);
    return EXIT_SUCCESS;
}
