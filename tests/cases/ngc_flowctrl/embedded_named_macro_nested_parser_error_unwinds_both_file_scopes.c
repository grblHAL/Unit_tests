#define NAMED_MACRO_BODY "#100=#1\nO<inner>CALL[4]\n#100=88\n"
#define INNER_MACRO_BODY "#102=#1\nG999\n#102=77\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    ram_expected_root_status = Status_GcodeUnsupportedCommand;
    run_named_macro_protocol("#1=99\n#101=0\nO<fixture>CALL[3]\n#101=7\n");
    NEAR(ram_flow_parameter(100), 3);
    NEAR(ram_flow_parameter(102), 4);
    NEAR(ram_flow_parameter(101), 0);
    NEAR(ram_flow_parameter(1), 99);
    CHECK(strstr(engine_output, "inner.macro") != NULL);
    return EXIT_SUCCESS;
}
