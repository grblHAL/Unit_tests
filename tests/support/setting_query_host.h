#pragma once
#include "support/settings_host.h"
#include "system.h"
#include <stdio.h>
#include "report.h"
#include "state_machine.h"
static control_signals_t query_control_state(void) { return (control_signals_t){0}; }
static bool query_connected(void) { return true; }
static inline void prepare_setting_query(void)
{
    prepare_settings_store();
    hal.control.get_state = query_control_state;
    hal.stream.is_connected = query_connected;
    report_init_fns(); report_init();
    state_set(STATE_IDLE);
}
static inline void check_integer_setting_query(setting_id_t id, uint32_t expected)
{
    const setting_detail_t *detail = setting_get_details(id, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == expected);
    char command[32], line[64];
    CHECK(snprintf(command, sizeof(command), "$%u", (unsigned)id) > 0);
    CHECK(snprintf(line, sizeof(line), "$%u=%lu" ASCII_EOL, (unsigned)id, (unsigned long)expected) > 0);
    engine_output[0] = '\0';
    CHECK(system_execute_line(command, hal.stream.write) == Status_OK);
    CHECK(strcmp(engine_output, line) == 0);
}
