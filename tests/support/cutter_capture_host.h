#pragma once
#include "support/cutter_parser_host.h"
static unsigned cutter_enable_calls;
static bool cutter_accept = true;
static gc_ccomp_t cutter_received;
static plane_t cutter_received_plane;
// Simulate accepting or refusing configuration, without implementing compensated geometry.
bool cc_enable(gc_ccomp_t *data, plane_t plane, coord_data_t *position)
{
    CHECK(position == (coord_data_t *)gc_state.position);
    cutter_enable_calls++; cutter_received = *data; cutter_received_plane = plane;
    if(cutter_accept) data->first_move = data->side != CComp_Off;
    return cutter_accept;
}
static inline void prepare_cutter_capture(void)
{ prepare_cutter_parser(); cutter_enable_calls = 0; }
