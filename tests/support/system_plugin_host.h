#pragma once
#include "support/system_command_host.h"
static unsigned plugin_calls, unknown_calls;
static status_code_t plugin_status = Status_OK, unknown_status = Status_OK;
static char plugin_args[96], unknown_line[96], redirected_output[256];
static status_code_t plugin_execute(sys_state_t state, char *args)
{
    CHECK(state == STATE_IDLE);
    plugin_calls++;
    if(args) { CHECK(strlen(args) < sizeof(plugin_args)); strcpy(plugin_args, args); }
    hal.stream.write("reply:");
    if(args) hal.stream.write(args);
    return plugin_status;
}
static inline status_code_t plugin_unknown(sys_state_t state, char *line)
{
    CHECK(state == STATE_IDLE && strlen(line) < sizeof(unknown_line));
    unknown_calls++;
    strcpy(unknown_line, line);
    return unknown_status;
}
static void redirected_write(const char *text)
{
    CHECK(strlen(redirected_output) + strlen(text) < sizeof(redirected_output));
    strcat(redirected_output, text);
}
static inline void prepare_system_plugin(void)
{
    prepare_system_command();
    static const sys_command_t items[] = {
        {.command = "ECHO", .execute = plugin_execute, .flags = {.allow_redirect = true}},
        {.command = "PRIVATE", .execute = plugin_execute},
        {.command = "BLOCKOK", .execute = plugin_execute, .flags = {.noargs = true, .allow_blocking = true}},
        {.command = "PING", .execute = plugin_execute, .flags = {.noargs = true}}
    };
    static sys_commands_t commands = {.n_commands = 4, .commands = items};
    system_register_commands(&commands);
}
static inline status_code_t redirected_command(const char *text)
{
    char line[96];
    CHECK(strlen(text) < sizeof(line));
    strcpy(line, text);
    return system_execute_line(line, redirected_write);
}
