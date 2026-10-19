#define NAMED_MACRO_BODY "#100=#1\nG999\n#100=88\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    ram_expected_root_status = Status_GcodeUnsupportedCommand;
    run_named_macro_protocol("#1=99\n#101=0\nO<fixture>CALL[12]\n#101=7\n");
    NEAR(ram_flow_parameter(100), 12);
    NEAR(ram_flow_parameter(101), 0);
    NEAR(ram_flow_parameter(1), 99);
    CHECK(strstr(engine_output, "fixture.macro") != NULL);
    return EXIT_SUCCESS;
}
