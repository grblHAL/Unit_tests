#include "analog_host.h"
int main(void)
{
    prepare_analog();
    initialize_analog();
    CHECK(starts == 1 && probes == 1 && registrations == 1 && native_enumerations == 1);
    xbar_t *pin = bank.get_pin_info(DEVICE_DIRECTION, 0);
    CHECK(pin && pin->cap.external && pin->cap.analog && pin->cap.claimable);
    CHECK(pin->cap.resolution == Resolution_12bit && pin->function == DEVICE_FUNCTION + 3);
#ifdef MCP4725_ENABLE
    CHECK(sends == 2 && reads == 1 && pin->get_value(pin) == 0xabc);
#else
    CHECK(sends == 0 && reads == 0 && pin->get_value(pin) == 0xabc);
    CHECK(reads == 1);
#endif
    CHECK(bank.get_pin_info(DEVICE_DIRECTION, 1) == NULL);
    CHECK(bank.get_pin_info(DEVICE_DIRECTION == Port_Input ? Port_Output : Port_Input, 0) == NULL);
    return 0;
}
