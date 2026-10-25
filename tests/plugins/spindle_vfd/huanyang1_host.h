#pragma once
#include "vfd_host.h"
static inline void expect_frame(unsigned index, uint8_t function, uint8_t length, uint8_t a,
                                uint8_t c, uint8_t d, bool block)
{
    CHECK(index < vfd_requests);
    const modbus_message_t *m = &vfd_messages[index];
    CHECK(m->adu[0] == 1 && m->adu[1] == function && m->tx_length == length);
    CHECK(m->adu[2] == a && m->adu[3] == c && m->adu[4] == d);
    CHECK(vfd_blocking[index] == block);
}
static inline void expect_discovery(unsigned start)
{
    const uint8_t parameters[] = {0x90, 0x0b, 0x05, 0x8e};
    for (unsigned i = 0; i < 4; i++)
        expect_frame(start + i, ModBus_ReadCoils, 8, 3, parameters[i], 0, true);
}
