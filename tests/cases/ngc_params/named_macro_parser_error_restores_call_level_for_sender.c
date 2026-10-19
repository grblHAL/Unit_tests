#define NAMED_MACRO_BODY "#100=#<_call_level>\nO<inner>CALL\n"
#define INNER_MACRO_BODY "#101=#<_call_level>\nG999\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    ram_expected_root_status = Status_GcodeUnsupportedCommand;
    ram_sender_query = "#102=#<_call_level>\n$G\n";
    run_named_macro_protocol("O<fixture>CALL\n#103=99\n");
    NEAR(ram_flow_parameter(100), 1);
    NEAR(ram_flow_parameter(101), 2);
    NEAR(ram_flow_parameter(102), 0);
    NEAR(ram_flow_parameter(103), 0);
    return EXIT_SUCCESS;
}
