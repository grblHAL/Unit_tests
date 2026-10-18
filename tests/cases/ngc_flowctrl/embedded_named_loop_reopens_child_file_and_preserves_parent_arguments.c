#define NAMED_MACRO_BODY "#100=0\n#101=0\nO10WHILE[#100LT3]\n#100=[#100+1]\nO<inner>CALL[#100]\nO10ENDWHILE\n#102=#1\n"
#define INNER_MACRO_BODY "#101=[#101+#1]\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("#1=99\n#100=0\n#101=0\nO<fixture>CALL[12]\n#103=#1\n");
    NEAR(ram_flow_parameter(100), 3);
    NEAR(ram_flow_parameter(101), 6);
    NEAR(ram_flow_parameter(102), 12);
    NEAR(ram_flow_parameter(103), 99);
    return EXIT_SUCCESS;
}
