#pragma once
#include <string.h>
#include "grbl/hal.h"
int atci_digital_in(unsigned port, unsigned pin);
#define DIGITAL_IN(p, n) atci_digital_in(p, n)
#define AUXINPUT0_PORT 0
#define AUXINPUT0_PIN 0
#define AUXINPUT1_PORT 0
#define AUXINPUT1_PIN 1
#define AUXINPUT2_PORT 0
#define AUXINPUT2_PIN 2
#define AUXINPUT7_PORT 0
#define AUXINPUT7_PIN 7
