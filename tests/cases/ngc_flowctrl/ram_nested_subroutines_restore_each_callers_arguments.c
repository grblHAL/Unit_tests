#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_root_protocol("#1=99\n#100=0\nO10SUB\n#100=[#100+#1]\nO20CALL[4]\n#102=#1\nO10ENDSUB\nO20SUB\n#100=[#100+#1]\nO30CALL[5]\n#103=#1\nO20ENDSUB\nO30SUB\n#100=[#100+#1]\nO30ENDSUB\nO10CALL[3]\n#101=7\n");
    NEAR(ram_flow_parameter(100), 12);
    NEAR(ram_flow_parameter(102), 3);
    NEAR(ram_flow_parameter(103), 4);
    NEAR(ram_flow_parameter(1), 99);
    NEAR(ram_flow_parameter(101), 7);
    return EXIT_SUCCESS;
}
