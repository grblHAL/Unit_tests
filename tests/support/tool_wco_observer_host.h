#pragma once
#include "support/tool_change_host.h"
static unsigned tool_wco_events;
static coord_system_id_t tool_wco_id;
static coord_system_data_t tool_wco_data;
static void observe_tool_wco(coord_system_id_t id, coord_system_data_t *data)
{
    CHECK(data != NULL);
    tool_wco_events++;
    tool_wco_id = id;
    tool_wco_data = *data;
}
static inline void prepare_tool_wco_observer(void)
{
    prepare_tool_change_with_wco_observer(observe_tool_wco);
    CHECK(grbl.on_wco_saved != observe_tool_wco);
}
static inline void tool_wco_block(const char *text)
{
    char block[80];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    CHECK(gc_execute_block(block) == Status_OK);
}
static inline void acknowledge_and_start_tool_change(void)
{
    grbl.on_toolchange_ack();
    CHECK(tool_stream_handler(CMD_CYCLE_START));
    engine_execute_tasks(STATE_TOOL_CHANGE);
}
