#include "support/boot_host.h"

static io_stream_t serial_base, bluetooth_client, websocket_client;
static char client_output[4096];
static enqueue_realtime_command_ptr base_rt, client_rt;
static enqueue_realtime_command_ptr set_base_rt(enqueue_realtime_command_ptr handler)
{ enqueue_realtime_command_ptr previous = base_rt; if(handler) base_rt = handler; return previous; }
static enqueue_realtime_command_ptr set_client_rt(enqueue_realtime_command_ptr handler)
{ enqueue_realtime_command_ptr previous = client_rt; if(handler) client_rt = handler; return previous; }
static void write_client(const char *text)
{
    CHECK(strlen(client_output) + strlen(text) < sizeof(client_output));
    strcat(client_output, text);
}
static void connect_early_clients(void)
{
    CHECK(!sys.driver_started && boot_setup_calls == 0);
    serial_base = hal.stream;
    serial_base.type = StreamType_Serial;
    serial_base.set_enqueue_rt_handler = set_base_rt;
    CHECK(stream_connect(&serial_base));
    bluetooth_client = serial_base;
    bluetooth_client.type = StreamType_Bluetooth;
    bluetooth_client.write = write_client;
    bluetooth_client.set_enqueue_rt_handler = set_client_rt;
    CHECK(stream_connect(&bluetooth_client));
    CHECK(hal.stream.type == StreamType_Bluetooth && client_rt == protocol_enqueue_realtime_command);
    CHECK(client_output[0] == 0);
    CHECK(strstr(engine_output, "BLUETOOTH STREAM ACTIVE") != NULL);
    stream_disconnect(&bluetooth_client);
    CHECK(hal.stream.type == StreamType_Serial && base_rt == protocol_enqueue_realtime_command);
    CHECK(client_output[0] == 0);
    websocket_client = bluetooth_client;
    websocket_client.type = StreamType_WebSocket;
    CHECK(stream_connect(&websocket_client));
    CHECK(hal.stream.type == StreamType_WebSocket);
    CHECK(client_output[0] == 0 && !sys.driver_started);
    CHECK(strstr(engine_output, "WEBSOCKET STREAM ACTIVE") != NULL);
}
int main(void)
{
    boot_during_init = connect_early_clients;
    boot_program = "$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    const char *welcome = strstr(client_output, "GrblHAL ");
    CHECK(welcome != NULL);
    CHECK(strstr(welcome + strlen("GrblHAL "), "GrblHAL ") == NULL);
    CHECK(strstr(welcome, "[GC:") != NULL && strstr(welcome, "ok" ASCII_EOL) != NULL);
    CHECK(strstr(client_output, "error:") == NULL);
    CHECK(stream_get_base() == &serial_base && hal.stream.type == StreamType_WebSocket);
    CHECK(client_rt == protocol_enqueue_realtime_command);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
