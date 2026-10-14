#pragma once
#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"
#include <string.h>
static unsigned legacy_description_calls[2];
static char legacy_descriptions[2][32][8];
static void legacy_description(io_port_type_t type, io_port_direction_t dir, uint8_t port, const char *text)
{
    CHECK(type == Port_Digital || type == Port_Analog);
    CHECK(port < 32 && strlen(text) < 8);
    strcpy(legacy_descriptions[dir][port], text); legacy_description_calls[dir]++;
}
static inline void prepare_legacy_ports(void)
{ engine_prepare(); hal.port.set_pin_description = legacy_description; }
