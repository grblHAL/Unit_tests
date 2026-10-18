#define NAMED_MACRO_BODY "#100=[#100+#1]\nO<inner>CALL[4]\n#102=#1\n"
#define INNER_MACRO_BODY "#100=[#100+#1]\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("#1=99\n#100=0\nO<fixture>CALL[3]\n#101=#1\n");
    NEAR(ram_flow_parameter(100), 7);
    NEAR(ram_flow_parameter(101), 99);
    NEAR(ram_flow_parameter(102), 3);
    return EXIT_SUCCESS;
}
