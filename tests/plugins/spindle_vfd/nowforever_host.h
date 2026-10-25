#pragma once
#include "vfd_host.h"
static inline void expect_write(unsigned index, uint16_t reg, uint16_t value, bool block)
{
    CHECK(index < vfd_requests);
    const modbus_message_t *m = &vfd_messages[index];
    CHECK(m->tx_length == 11 && m->rx_length == 8);
    CHECK(m->adu[0] == 1 && m->adu[1] == ModBus_WriteRegisters);
    CHECK(((m->adu[2] << 8) | m->adu[3]) == reg);
    CHECK(m->adu[4] == 0 && m->adu[5] == 1 && m->adu[6] == 2);
    CHECK(((m->adu[7] << 8) | m->adu[8]) == value);
    CHECK(vfd_blocking[index] == block);
}
