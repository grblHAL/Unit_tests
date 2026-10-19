#define NAMED_MACRO_BODY ""
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("#1=99\nO<fixture>CALL[12]\n#100=#1\n");
    NEAR(ram_flow_parameter(100), 99);
    return EXIT_SUCCESS;
}
