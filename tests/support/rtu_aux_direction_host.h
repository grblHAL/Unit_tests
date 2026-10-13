#pragma once
#include "support/rtu_host.h"
#include "support/ioports_host.h"
static unsigned direction_assignments;
static bool assign_direction_function(xbar_t *pin, pin_function_t function)
{
    CHECK(pin == &digital_pins[Port_Output][0] || pin == &digital_pins[Port_Output][1]);
    CHECK(function == Output_RS485_Direction);
    direction_assignments++;
    return true;
}
static void configure_rtu_aux_outputs(void)
{
    for(unsigned i = 0; i < 2; i++) {
        digital_pins[Port_Output][i].mode.output = true;
        digital_pins[Port_Output][i].set_function = assign_direction_function;
    }
    register_ioports();
}
static inline void prepare_rtu_aux_direction(int8_t direction)
{
    prepare_rtu_transport(NULL, direction, configure_rtu_aux_outputs);
}
static inline void verify_aux_direction_exchange(uint8_t expected_pin)
{
    CHECK(direction_assignments == 1);
    send_request();
    inject_reply(false);
    for(unsigned i = 0; i < 5 && rx_calls == 0; i++) poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    fprintf(stderr, "direction writes=%u\n", output_calls);
    CHECK(output_calls == 2);
    CHECK(output_log[0] && !output_log[1]);
    CHECK(output_pin_log[0] == expected_pin && output_pin_log[1] == expected_pin);
}
