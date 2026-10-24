#include "support/ram_macro_protocol_host.h"

int main(void)
{
    ram_expected_root_status = Status_ExpressionDivideByZero;
    ram_sender_query = "$G\nO20IF[1]\n#101=7\nO20ENDIF\n$G\n";
    run_ram_root_protocol("#100=0\n#101=0\n#102=5\n#103=0\nO10IF[1/#100]\n#103=99\nO10ENDIF\n#102=99\n");
    NEAR(ram_flow_parameter(100), 0);
    NEAR(ram_flow_parameter(101), 7);
    NEAR(ram_flow_parameter(102), 5);
    NEAR(ram_flow_parameter(103), 0);
    CHECK(plan_get_current_block() == NULL && sys.flags.exit && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
