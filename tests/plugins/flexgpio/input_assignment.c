#include "flex_host.h"
int main(void)
{
    flex_start();
    xbar_t selected = flex_pin(Port_Input, 0);
    xbar_t neighbor = flex_pin(Port_Input, 1);
    const pin_function_t original = selected.function;
    const pin_function_t assigned = Input_Aux0 + 12;
    CHECK(selected.set_function && selected.set_function(&selected, assigned));
    xbar_t readback = flex_pin(Port_Input, 0);
    CHECK(readback.function == assigned && readback.id == selected.id);
    CHECK(readback.pin == selected.pin && readback.port == selected.port);
    CHECK(flex_pin(Port_Input, 1).function == neighbor.function);
    CHECK(readback.set_function(&readback, original));
    CHECK(flex_pin(Port_Input, 0).function == original);
    CHECK(alarms == 0);
    return 0;
}
