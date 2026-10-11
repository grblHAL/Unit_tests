#pragma once
#include "support/ioports_host.h"
static unsigned assignment_calls;
static pin_function_t assigned_function;
static bool assignment_result = true;
static xbar_t *assignment_pin;
static bool driver_assign_function(xbar_t *pin, pin_function_t function)
{
    CHECK(pin == assignment_pin);
    assignment_calls++;
    assigned_function = function;
    return assignment_result;
}
static inline xbar_t *prepare_assignment(io_port_direction_t direction)
{
    prepare_ioports();
    assignment_pin = hal.port.get_pin_info(Port_Digital, direction, 0);
    CHECK(assignment_pin != NULL);
    assignment_pin->mode.output = direction == Port_Output;
    assignment_pin->mode.input = direction == Port_Input;
    assignment_pin->set_function = driver_assign_function;
    return assignment_pin;
}
