#pragma once
#include "support/analog_motion_host.h"
#include "support/queued_motion_rejection_host.h"
static inline void claim_fixture_ports(io_port_type_t type, io_port_direction_t direction, uint8_t claimed[2])
{
    CHECK(ioports_unclaimed(type, direction) == 2);
    for(unsigned i = 0; i < 2; i++) {
        uint8_t port = (uint8_t)i;
        CHECK(ioport_claim(type, direction, &port, "Plugin device") != NULL);
        claimed[i] = port;
    }
    CHECK(ioports_unclaimed(type, direction) == 0);
}
