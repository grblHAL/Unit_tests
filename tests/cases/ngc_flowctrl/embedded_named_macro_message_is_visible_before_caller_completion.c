#define NAMED_MACRO_BODY "(MSG,fixture macro done)\n#100=#1\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("O<fixture>CALL[12]\n#101=7\n");
    NEAR(ram_flow_parameter(100), 12);
    NEAR(ram_flow_parameter(101), 7);
    CHECK(strstr(engine_output, "fixture macro done") != NULL);
    return EXIT_SUCCESS;
}
