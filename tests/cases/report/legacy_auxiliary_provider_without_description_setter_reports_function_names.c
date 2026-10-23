#include "support/report_host.h"
#include "support/ioports_host.h"
static xbar_t *legacy_info(io_port_type_t type, io_port_direction_t dir, uint8_t port)
{
    return type == Port_Digital ? pin_info(dir, port) : NULL;
}
static bool legacy_claim(io_port_type_t type, io_port_direction_t dir, uint8_t *port, const char *description)
{
    xbar_t *pin = legacy_info(type, dir, *port);
    if(!pin || pin->mode.claimed) return false;
    pin->mode.claimed = true;
    pin->description = description;
    return true;
}
static int32_t legacy_read(io_port_type_t type, uint8_t port, wait_mode_t mode, float timeout)
{
    CHECK(type == Port_Digital);
    return pin_read(port, mode, timeout);
}
int main(void)
{
    prepare_report();
    hal.port.get_pin_info = legacy_info;
    hal.port.claim = legacy_claim;
    hal.port.digital_out = pin_output;
    hal.port.wait_on_input = legacy_read;
    CHECK(hal.port.set_pin_description == NULL);
    for(unsigned port = 0; port < 2; port++) {
        digital_pins[Port_Input][port].pin = (uint8_t)(7 + port);
        digital_pins[Port_Input][port].mode.input = true;
        digital_pins[Port_Input][port].cap.claimable = true;
        digital_pins[Port_Output][port].pin = (uint8_t)(9 + port);
        digital_pins[Port_Output][port].mode.output = true;
        digital_pins[Port_Output][port].cap.claimable = true;
    }
    io_ports_data_t ports = {0};
    CHECK(ioports_add(&ports, Port_Digital, 2, 2));
    ioport_digital_out(1, true);
    CHECK(output_calls == 1 && physical_output == 1 && output_value);
    CHECK(report_pin_states(STATE_IDLE, NULL) == Status_OK);
    CHECK(strstr(engine_output, "[PINSTATE:DIN|Aux in 0|7|N---|----|?]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[PINSTATE:DOUT|Aux out 0|9|N|-|?]" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "[PINSTATE:DIN|Aux in 1|8|") != NULL);
    CHECK(strstr(engine_output, "[PINSTATE:DOUT|Aux out 1|10|") != NULL);
    CHECK(output_calls == 1 && output_value && read_calls == 0);
    CHECK(ioports_unclaimed(Port_Digital, Port_Input) == 2);
    CHECK(ioports_unclaimed(Port_Digital, Port_Output) == 2);
    return EXIT_SUCCESS;
}
