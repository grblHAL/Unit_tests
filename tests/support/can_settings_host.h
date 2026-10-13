#pragma once
#include "support/settings_host.h"
#include "canbus.h"

static uint32_t selected_can_baud;
static unsigned can_baud_calls;
static bool accept_can_baud = true;
bool can_set_baud(uint32_t baud)
{
    selected_can_baud = baud;
    can_baud_calls++;
    return accept_can_baud;
}
static inline void prepare_can_settings(void)
{
    prepare_settings_store();
    canbus_init();
}
