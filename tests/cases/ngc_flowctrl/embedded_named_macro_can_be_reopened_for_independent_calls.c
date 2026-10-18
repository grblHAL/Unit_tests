#define NAMED_MACRO_BODY "#100=[#100+#1]\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("#100=0\nO<fixture>CALL[3]\nO<fixture>CALL[4]\n#101=7\n");
    NEAR(ram_flow_parameter(100), 7);
    NEAR(ram_flow_parameter(101), 7);
    return EXIT_SUCCESS;
}
