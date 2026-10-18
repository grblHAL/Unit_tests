#define NAMED_MACRO_BODY "#100=[#100+1]\nO10IF[#1GT0]\nO<fixture>CALL[#1-1]\nO10ENDIF\nO<fixture>RETURN[#1+10]\n#100=88\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("#1=99\n#100=0\n#101=0\nO<fixture>CALL[3]\n#102=#<_value>\n#103=#<_value_returned>\n#104=#1\n");
    NEAR(ram_flow_parameter(100), 4);
    fprintf(stderr, "Return value=%g caller=%g visits=%g\n", (double)ram_flow_parameter(102), (double)ram_flow_parameter(1), (double)ram_flow_parameter(100));
    NEAR(ram_flow_parameter(103), 1);
    NEAR(ram_flow_parameter(104), 99);
    NEAR(ram_flow_parameter(102), 13);
    return EXIT_SUCCESS;
}
