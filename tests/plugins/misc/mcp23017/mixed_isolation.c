#include "input_host.h"
int main(void)
{
    start_inputs();
    sample = 0xa5;
    ports.digital_out(7, true);
    CHECK(output_value == 128);
    CHECK(ports.wait_on_input(0, WaitMode_Immediate, 0) == 1);
    CHECK(ports.wait_on_input(1, WaitMode_Immediate, 0) == 0);
    ports.digital_out(0, true);
    CHECK(output_value == 129);
    CHECK(ports.wait_on_input(7, WaitMode_Immediate, 0) == 1);
    ports.digital_out(7, false);
    CHECK(output_value == 1 && sample == 0xa5);
    return 0;
}
