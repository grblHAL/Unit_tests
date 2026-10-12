#pragma once
#include "support/engine_host.h"
#include "canbus.h"
#include "check.h"
static can_rx_enqueue_fn can_receive;
static unsigned tx_calls;
static canbus_message_t tx_frame;
static bool tx_extended, tx_ready = true;
bool can_start(uint32_t baud, can_rx_enqueue_fn callback)
{
    CHECK(baud == 125000);
    can_receive = callback;
    return true;
}
bool can_put(canbus_message_t message, bool extended)
{
    tx_calls++;
    tx_frame = message;
    tx_extended = extended;
    CHECK(tx_frame.len <= 8);
    return tx_ready;
}
static inline void prepare_can(void)
{
    engine_prepare();
    setting_details_t *details = NULL;
    canbus_init();
    CHECK(setting_get_details(Setting_CANbus_BaudRate, &details) != NULL);
    CHECK(details != NULL && details->load != NULL);
    details->load();
    CHECK(canbus_enabled() && can_receive != NULL);
    CHECK(tx_calls == 0 && !tx_extended);
}
static inline void poll_can(void)
{
    engine_ticks++;
    engine_execute_tasks(STATE_IDLE);
}
