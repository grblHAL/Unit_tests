#pragma once
#include "support/engine_host.h"
#include "probe.h"
#include "check.h"
static bool probe_inputs[3];
static bool read_multiple_probe_input(void *input) { return *(bool *)input; }
static void register_multiple_probes(void)
{
    for(unsigned i = 0; i < 3; i++)
        CHECK(probe_add((probe_id_t)i, (uint8_t)i, IRQ_Mode_None,
                        &probe_inputs[i], read_multiple_probe_input));
    CHECK(hal.probe.select(Probe_Default));
    hal.probe.configure(false, false);
}

static inline void prepare_multiple_probes(void)
{
    engine_prepare();
    register_multiple_probes();
}
