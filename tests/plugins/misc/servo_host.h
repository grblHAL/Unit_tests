#pragma once
#include "misc_host.h"
#include "ioports.h"
void pwm_servo_init(void);
void prepare_servos(bool fail_config, bool readback);
extern unsigned servo_configs, servo_descriptions, servo_outputs;
extern float angles[2];
extern bool reject_config, use_readback;
