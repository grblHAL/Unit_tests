#pragma once
#include "driver.h"
#include "check.h"
#include "grbl/task.h"
#include "grbl/nvs_buffer.h"
#include "mpg_transport.h"
void mpg_init(void);
void mpg_prepare(void);
void mpg_start(void);
void mpg_poll(void);
void mpg_receive(uint8_t seq, mpg_frame_type_t type, const uint8_t *data, uint8_t size);
void mpg_bytes(const uint8_t *data, size_t size);
void mpg_up(void);
status_code_t mpg_command(const char *argument);
void mpg_ack(unsigned packet);
extern io_stream_t proxy;
extern setting_details_t *registered_settings;
extern unsigned claims, registrations, rt_calls, resets, warnings, saves, packets, chains;
extern bool alloc_ok, settings_ok, claim_ok, register_ok, baud_ok;
extern uint32_t now, baud;
extern char output[4096];
extern struct mpg_packet
{
    uint8_t data[256];
    size_t size;
} sent[256];
