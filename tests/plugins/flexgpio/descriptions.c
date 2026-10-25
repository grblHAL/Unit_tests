#include "flex_host.h"
int main(void)
{
    flex_start();
    bank.set_pin_description(Port_Input, 0, "Tool sensor");
    bank.set_pin_description(Port_Output, 0, "Solenoid");
    xbar_t pin = flex_pin(Port_Input, 0);
    CHECK(strcmp(pin.description, "Tool sensor") == 0);
    pin = flex_pin(Port_Output, 0);
    CHECK(strcmp(pin.description, "Solenoid") == 0);
    return 0;
}
