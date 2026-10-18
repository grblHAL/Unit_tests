#define NAMED_MACRO_BODY "#100=[#100+1]\nO10IF[#1GT0]\nO<fixture>CALL[#1-1]\nO10ELSE\nG999\nO10ENDIF\n#101=88\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    ram_expected_root_status = Status_GcodeUnsupportedCommand;
    run_named_macro_protocol("#1=99\n#100=0\n#101=0\nO<fixture>CALL[3]\n#101=7\n");
    NEAR(ram_flow_parameter(100), 4);
    NEAR(ram_flow_parameter(101), 0);
    NEAR(ram_flow_parameter(1), 99);
    CHECK(strstr(engine_output, "fixture.macro") != NULL);
    return EXIT_SUCCESS;
}
