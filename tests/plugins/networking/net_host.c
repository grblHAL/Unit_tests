#include "net_host.h"
system_t sys;
grbl_hal_t hal;
grbl_t grbl;
network_info_t net_infos[2];
bool net_available[2] = {true, true}, net_file;
unsigned net_previous_reports, net_previous_streams, net_registrations;
char net_output[4096];
static const char eth_name[] = "eth0", wifi_name[] = "wlan0";
static sys_commands_t *commands;
static network_info_t *info(const char *name)
{
    for (unsigned i = 0; i < 2; i++)
        if (name == net_infos[i].interface && net_available[i])
            return &net_infos[i];
    return NULL;
}
static void output(const char *text)
{
    CHECK(strlen(net_output) + strlen(text) < sizeof(net_output));
    strcat(net_output, text);
}
void report_message(const char *text, message_type_t type)
{
    CHECK(type == Message_Plain);
    output(text);
    output("\n");
}
static void report_options(bool newopt)
{
    (void)newopt;
    net_previous_reports++;
}
static void stream_changed(void) { net_previous_streams++; }
void system_register_commands(sys_commands_t *value)
{
    CHECK(value->n_commands == 1 && !strcmp(value->commands[0].command, "NETIF"));
    commands = value;
    net_registrations++;
}
status_code_t net_command(void)
{
    CHECK(commands);
    return commands->commands[0].execute(STATE_IDLE, NULL);
}
bool stream_is_file(void) { return net_file; }
void net_clear(void) { net_output[0] = 0; }
void net_prepare(void)
{
    hal.stream.write = output;
    grbl.on_report_options = report_options;
    grbl.on_stream_changed = stream_changed;
    networking_init();
    networking.get_info = info;
    net_infos[0] =
        (network_info_t){.interface = eth_name,
                         .is_ethernet = true,
                         .dhcp = true,
                         .status = {.ip = "192.168.1.20",
                                    .hostname = "mill",
                                    .telnet_port = 23,
                                    .websocket_port = 81,
                                    .services = {.telnet = On, .websocket = On, .mdns = On}}};
    strcpy(net_infos[0].mac, "02:00:00:01:02:03");
    net_infos[1] = (network_info_t){.interface = wifi_name,
                                    .wifi_mode = WiFiMode_STA,
                                    .status = {.ip = "192.168.1.21",
                                               .hostname = "mill",
                                               .websocket_port = 81,
                                               .services = {.websocket = On, .mdns = On}}};
    strcpy(net_infos[1].mac, "02:00:00:04:05:06");
}
void net_add(unsigned index, network_status_t status)
{
    CHECK(index < 2);
    networking.event(net_infos[index].interface, status);
}
bool protocol_execute_realtime(void)
{
    CHECK(false);
    return false;
}
bool protocol_exec_rt_system(void)
{
    CHECK(false);
    return false;
}
bool state_door_reopened(void)
{
    CHECK(false);
    return false;
}
