#include "servo_host.h"
unsigned servo_configs, servo_descriptions, servo_outputs;
float angles[2];
bool reject_config, use_readback;
static bool configure(xbar_t *pin, xbar_cfg_ptr_t value, bool persistent)
{
 const pwm_config_t *config = value.pwm_config;
 CHECK(pin->id < 2 && !persistent); servo_configs++;
 NEAR(config->freq_hz, 50); NEAR(config->min, 0); NEAR(config->max, 180);
 NEAR(config->min_value, 2.72f); NEAR(config->max_value, 12.0f);
 CHECK(config->servo_mode && !config->invert); CHECK(config->off_value < 0);
 return !reject_config;
}
static float get_angle(xbar_t *pin) { CHECK(pin->id < 2); return angles[pin->id]; }
bool ioports_enumerate(io_port_type_t type, io_port_direction_t dir, pin_cap_t filter, ioports_enumerate_callback_ptr callback, void *data)
{
 CHECK(type == Port_Analog && dir == Port_Output && filter.pwm && filter.claimable);
 for(unsigned i = 0; i < 2; i++) {
  xbar_t pin = {.id = i, .config = configure, .get_value = use_readback ? get_angle : NULL};
  if(callback(&pin, (uint8_t)(i + 4), data)) return true;
 }
 return false;
}
bool ioport_set_description(io_port_type_t type, io_port_direction_t dir, uint8_t port, const char *description)
{
 CHECK(type == Port_Analog && dir == Port_Output && port >= 4 && port < 6);
 CHECK(strncmp(description, "PWM Servo ", 10) == 0); servo_descriptions++; return true;
}
bool ioport_analog_out(uint8_t port, float angle)
{ CHECK(port >= 4 && port < 6); angles[port - 4] = angle; servo_outputs++; return true; }
void prepare_servos(bool fail_config, bool readback)
{ prepare_hooks(); reject_config = fail_config; use_readback = readback; pwm_servo_init(); }
