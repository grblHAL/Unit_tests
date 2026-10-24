#pragma once
#include <stdint.h>
extern uint8_t rp_memory[2016 * 1024 + 4096];
#define XIP_BASE ((uintptr_t)rp_memory)
