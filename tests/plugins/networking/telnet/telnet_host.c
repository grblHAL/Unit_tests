#include "telnet_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
networking_t networking;
const ip_addr_t ip_addr_any = {0};
static struct tcp_pcb listener;
struct tcp_pcb telnet_client;
unsigned tcp_acks, tcp_frees, tcp_outputs, tcp_closes, tcp_aborts, network_events;
unsigned rt_calls, block_calls;
bool tcp_bind_ok = true;
uint8_t tcp_bytes[2048];
size_t tcp_length;
err_t tcp_write_result = ERR_OK;
tcp_accept_fn listener_accept;
void *listener_arg;
static struct pbuf packets[2];
static bool packet_live;
struct tcp_pcb *tcp_new(void) { return &listener; }
err_t tcp_bind(struct tcp_pcb *pcb, const ip_addr_t *address, u16_t port)
{
    CHECK(pcb == &listener && address == IP_ADDR_ANY && port == 2323);
    return tcp_bind_ok ? ERR_OK : ERR_USE;
}
struct tcp_pcb *tcp_listen_with_backlog(struct tcp_pcb *pcb, u8_t backlog)
{
    CHECK(pcb == &listener && backlog == TCP_DEFAULT_LISTEN_BACKLOG);
    return pcb;
}
void tcp_arg(struct tcp_pcb *pcb, void *arg)
{
    CHECK(pcb);
    pcb->callback_arg = arg;
    if (pcb == &listener)
        listener_arg = arg;
}
void tcp_accept(struct tcp_pcb *pcb, tcp_accept_fn callback)
{
    CHECK(pcb == &listener);
    listener_accept = callback;
}
void tcp_recv(struct tcp_pcb *pcb, tcp_recv_fn callback)
{
    CHECK(pcb);
    pcb->recv = callback;
}
void tcp_sent(struct tcp_pcb *pcb, tcp_sent_fn callback)
{
    CHECK(pcb);
    pcb->sent = callback;
}
void tcp_err(struct tcp_pcb *pcb, tcp_err_fn callback)
{
    CHECK(pcb);
    pcb->errf = callback;
}
void tcp_poll(struct tcp_pcb *pcb, tcp_poll_fn callback, u8_t interval)
{
    CHECK(pcb && interval);
    pcb->poll = callback;
}
void tcp_setprio(struct tcp_pcb *pcb, u8_t priority) { CHECK(pcb && priority == TCP_PRIO_MIN); }
void tcp_recved(struct tcp_pcb *pcb, u16_t count)
{
    CHECK(pcb == &telnet_client);
    tcp_acks += count;
}
u8_t pbuf_free(struct pbuf *packet)
{
    CHECK(packet == packets && packet_live);
    packet_live = false;
    tcp_frees++;
    return packets[1].len ? 2 : 1;
}
err_t tcp_write(struct tcp_pcb *pcb, const void *data, u16_t count, u8_t flags)
{
    CHECK(pcb == &telnet_client && data && count && flags == TCP_WRITE_FLAG_COPY);
    if (tcp_write_result != ERR_OK)
        return tcp_write_result;
    CHECK(tcp_length + count <= sizeof(tcp_bytes));
    memcpy(tcp_bytes + tcp_length, data, count);
    tcp_length += count;
    return ERR_OK;
}
err_t tcp_output(struct tcp_pcb *pcb)
{
    CHECK(pcb == &telnet_client);
    tcp_outputs++;
    return ERR_OK;
}
err_t tcp_close(struct tcp_pcb *pcb)
{
    CHECK(pcb);
    tcp_closes++;
    return ERR_OK;
}
void tcp_abort(struct tcp_pcb *pcb)
{
    CHECK(pcb);
    tcp_aborts++;
}
u32_t sys_now(void) { return 100; }
bool protocol_enqueue_realtime_command(uint8_t value)
{
    rt_calls++;
    return value == '!';
}
static bool block(void)
{
    block_calls++;
    return false;
}
static void write_base(const char *text) { CHECK(text); }
static int32_t read_base(void) { return SERIAL_NO_DATA; }
static uint16_t tx_count_base(void) { return 0; }
static enqueue_realtime_command_ptr base_handler(enqueue_realtime_command_ptr handler)
{
    CHECK(handler);
    return protocol_enqueue_realtime_command;
}
static const io_stream_t base = {.type = StreamType_Serial,
                                 .read = read_base,
                                 .write = write_base,
                                 .get_tx_buffer_count = tx_count_base,
                                 .set_enqueue_rt_handler = base_handler};
static void previous_event(const char *interface, network_status_t status)
{
    CHECK(interface && !strcmp(interface, "eth0"));
    (void)status;
    network_events++;
}
void telnet_prepare(void)
{
    memcpy(&hal.stream, &base, sizeof(base));
    CHECK(stream_connect(&base));
    hal.stream_blocking_callback = block;
    networking.event = previous_event;
}
void telnet_connect(void)
{
    telnet_prepare();
    CHECK(telnetd_init(2323) && listener_accept && listener_arg);
    CHECK(listener_accept(listener_arg, &telnet_client, ERR_OK) == ERR_OK);
    CHECK(hal.stream.type == StreamType_Telnet && hal.stream.is_connected());
}
void telnet_receive(const char *first, const char *second)
{
    CHECK(first && *first && !packet_live && telnet_client.recv);
    memset(packets, 0, sizeof(packets));
    packets[0].payload = (void *)first;
    packets[0].len = strlen(first);
    packets[0].tot_len = packets[0].len;
    if (second)
    {
        CHECK(*second);
        packets[0].next = &packets[1];
        packets[1].payload = (void *)second;
        packets[1].len = packets[1].tot_len = strlen(second);
        packets[0].tot_len += packets[1].len;
    }
    packet_live = true;
    CHECK(telnet_client.recv(telnet_client.callback_arg, &telnet_client, packets, ERR_OK) ==
          ERR_OK);
}
void telnet_finish(void)
{
    telnetd_stop();
    CHECK(hal.stream.type == StreamType_Serial && !packet_live);
}
void report_message(const char *text, message_type_t type) { CHECK(text && type == Message_Plain); }
sys_state_t state_get(void) { return STATE_IDLE; }
void report_add_realtime(report_tracking_t report)
{
    (void)report;
    CHECK(false);
}
void report_realtime_status(stream_write_ptr write, status_report_tracking_t *report)
{
    (void)write;
    (void)report;
    CHECK(false);
}
void report_gcode_modes(stream_write_ptr write)
{
    (void)write;
    CHECK(false);
}
report_tracking_flags_t report_get_rt_flags_all(void)
{
    CHECK(false);
    return (report_tracking_flags_t){0};
}
void gc_filestream_changed(vfs_file_t *file)
{
    (void)file;
    CHECK(false);
}
void task_execute(bool wait)
{
    (void)wait;
    CHECK(false);
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
    return false;
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t delay)
{
    (void)fn;
    (void)data;
    (void)delay;
    CHECK(false);
    return false;
}
void task_delete(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
}
void system_register_commands(sys_commands_t *commands)
{
    (void)commands;
    CHECK(false);
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

bool ioports_enumerate(io_port_type_t type, io_port_direction_t dir, pin_cap_t filter,
                       ioports_enumerate_callback_ptr callback, void *data)
{
    (void)type;
    (void)dir;
    (void)filter;
    (void)callback;
    (void)data;
    CHECK(false);
    return false;
}
bool ioport_digital_out(uint8_t port, uint32_t value)
{
    (void)port;
    (void)value;
    CHECK(false);
    return false;
}
bool task_run_on_startup(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
    return false;
}

static unsigned protection_depth;
sys_prot_t sys_arch_protect(void) { return protection_depth++; }
void sys_arch_unprotect(sys_prot_t previous)
{
    CHECK(protection_depth == previous + 1);
    protection_depth--;
}
