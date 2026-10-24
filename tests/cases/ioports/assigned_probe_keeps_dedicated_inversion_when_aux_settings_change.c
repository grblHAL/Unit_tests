#include "support/ioports_settings_host.h"
#include "probe.h"
static bool raw_probe;
static bool read_probe(void *input) { CHECK(input == &raw_probe); return raw_probe; }
static bool assign_probe(xbar_t *pin, pin_function_t function)
{
    CHECK(pin == &digital_pins[Port_Input][0] && function == Input_Probe);
    return true;
}
int main(void)
{
    prepare_io_settings();
    hal.driver_cap.probe = true;
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_None, &raw_probe, read_probe));
    xbar_t *probe_pin = hal.port.get_pin_info(Port_Digital, Port_Input, 0);
    probe_pin->set_function = assign_probe;
    probe_pin->mode.debounce = true;
    CHECK(ioport_set_function(probe_pin, Input_Probe, (driver_caps_t){0}));
    CHECK(ioports_available(Port_Digital, Port_Input) == 1);
    CHECK(store_io_setting(Setting_InvertProbePin, "1") == Status_OK);
    CHECK(captured_input[0].inverted && !captured_input[0].debounce);
    CHECK(hal.probe.get_state().triggered);
    unsigned calls = input_config_calls[0];
    CHECK(store_io_setting(Settings_IoPort_InvertIn, "2") == Status_OK);
    CHECK(input_config_calls[0] == calls && captured_input[0].inverted);
    CHECK(captured_input[1].inverted && hal.probe.get_state().triggered);
    CHECK(store_io_setting(Setting_InvertProbePin, "0") == Status_OK);
    CHECK(!captured_input[0].inverted && !captured_input[0].debounce);
    CHECK(!hal.probe.get_state().triggered && captured_input[1].inverted);
    CHECK(probe_pin->function == Input_Probe);
    return EXIT_SUCCESS;
}
