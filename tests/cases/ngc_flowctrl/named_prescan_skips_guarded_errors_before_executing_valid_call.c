#define NAMED_MACRO_BODY "O10IF[#1EQ0]\nO10ERROR[3]\nO10ENDIF\n#100=[#100+#1]\n"
#include "support/embedded_macro_protocol_host.h"
int main(void)
{
    run_named_macro_protocol("#1=99\n#100=0\nO<fixture>CALL[3]\nO<fixture>CALL[4]\n#101=#1\n");
    NEAR(ram_flow_parameter(100), 7);
    NEAR(ram_flow_parameter(101), 99);
    CHECK(sys.alarm == Alarm_None);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
