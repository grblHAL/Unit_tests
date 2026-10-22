#include "support/ram_g65_return_host.h"
int main(void)
{
    ram_macro_override = execute_returning_macro;
    run_ram_macro_protocol(
        "#1=3\nG65P10A5\n#101=#<_value>\nG91\n",
        "#1=9\nG65P20A7\n#102=#<_value>\nO10IF[1]\nO10RETURN[13]\nO10ENDIF\n#103=99\n",
        "#1=17\nO20IF[1]\nO20RETURN[17]\nO20ENDIF\n#104=99\n");
    CHECK(explicit_returns == 2 && grbl.on_macro_return == NULL);
    for(unsigned i = 0; i < 3; i++) CHECK(ram_macro_errors[i] == 0 && ram_return_status[i] == Status_OK);
    NEAR(ram_return_arguments[0], 3);
    NEAR(ram_return_arguments[1], 9);
    NEAR(ram_return_arguments[2], 17);
    NEAR(ram_flow_parameter(101), 13);
    NEAR(ram_flow_parameter(102), 17);
    NEAR(ram_flow_parameter(103), 0);
    NEAR(ram_flow_parameter(104), 0);
    CHECK(gc_state.modal.distance_incremental);
    return EXIT_SUCCESS;
}
