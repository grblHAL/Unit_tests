#pragma once
#include "support/ioports_host.h"
static unsigned pwm_config_calls;
static uint8_t claimed_pwm_port;
static xbar_t *configured_pwm_pin;
static pwm_config_t captured_pwm;
static bool pwm_config_result = true;
static bool configure_pwm(xbar_t *pin, xbar_cfg_ptr_t data, bool persistent)
{
    CHECK(!persistent);
    CHECK(data.pwm_config != NULL);
    configured_pwm_pin = pin;
    captured_pwm = *data.pwm_config;
    pwm_config_calls++;
    return pwm_config_result;
}
static inline void prepare_pwm_port(void)
{
    prepare_ioports();
    digital_pins[Port_Output][0].config = configure_pwm;
    digital_pins[Port_Output][0].cap.pwm = true;
    uint8_t port = 0;
    CHECK(ioport_claim(Port_Digital, Port_Output, &port, "PWM") != NULL);
    claimed_pwm_port = port;
    CHECK(ioport_get_info(Port_Digital, Port_Output, port) == &digital_pins[Port_Output][0]);
}
