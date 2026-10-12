#include "support/ioports_host.h"

int main(void)
{
    prepare_ioports();
    aux_ctrl_out_t control = {.port = 1, .function = Output_CoolantMist};
    pin_function_t function = Output_Aux1;
    ioport_assign_out_function(&control, &function);
    CHECK(function == Output_CoolantMist);
    return EXIT_SUCCESS;
}
