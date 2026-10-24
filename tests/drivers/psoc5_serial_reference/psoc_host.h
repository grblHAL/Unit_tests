#pragma once
#include <string.h>
#include "project.h"
#include "grbl/hal.h"
#include "grbl/protocol.h"
#include "serial.h"
#include "check.h"
void psoc_start(void);
void psoc_receive(const uint8_t *data, size_t size);
extern const io_stream_t *psoc_stream;
extern unsigned starts, rt_calls, clears, sent_count;
extern uint8_t sent[256];
