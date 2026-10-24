#include "support/ram_macro_protocol_host.h"

int main(void)
{
    ram_expected_root_status = Status_ExpressionDivideByZero;
    run_ram_root_protocol(
        "#100=1\n#101=0\n#102=7\nO10WHILE[1/#100]\n"
        "#101=[#101+1]\n#100=0\nO10CONTINUE\nO10ENDWHILE\n#102=99\n");
    NEAR(ram_flow_parameter(100), 0);
    NEAR(ram_flow_parameter(101), 1);
    NEAR(ram_flow_parameter(102), 7);
    CHECK(plan_get_current_block() == NULL && sys.flags.exit && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
