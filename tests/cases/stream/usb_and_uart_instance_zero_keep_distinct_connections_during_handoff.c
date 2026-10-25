#include "support/stream_connection_host.h"

static char uart_output[1024];
static enqueue_realtime_command_ptr uart_rt;
static void write_uart(const char *text)
{
    CHECK(strlen(uart_output) + strlen(text) < sizeof(uart_output));
    strcat(uart_output, text);
}
static enqueue_realtime_command_ptr set_uart_rt(enqueue_realtime_command_ptr handler)
{ enqueue_realtime_command_ptr previous = uart_rt; if(handler) uart_rt = handler; return previous; }
int main(void)
{
    prepare_report();
    io_stream_t usb = primary_connection;
    usb.state.is_usb = true;
    CHECK(stream_connect(&usb));
    CHECK(stream_connect(&secondary_connection));
    io_stream_t uart = primary_connection;
    uart.write = write_uart;
    uart.is_connected = NULL;
    uart.set_enqueue_rt_handler = set_uart_rt;
    CHECK(usb.instance == uart.instance && usb.state.is_usb && !uart.state.is_usb);
    clear_connection_output();
    CHECK(stream_connect(&uart));
    CHECK(hal.stream.type == StreamType_Serial && !hal.stream.state.is_usb);
    CHECK(hal.stream.is_connected != NULL && hal.stream.is_connected());
    CHECK(strstr(uart_output, "SERIAL STREAM ACTIVE") != NULL);
    CHECK(primary_output[0] == 0 && secondary_output[0] == 0);
    CHECK(uart_rt == protocol_enqueue_realtime_command);
    uart_output[0] = 0;
    hal.stream.write_all("all");
    CHECK(strcmp(primary_output, "all") == 0);
    CHECK(strcmp(secondary_output, "all") == 0);
    CHECK(strcmp(uart_output, "all") == 0);
    stream_disconnect(&uart);
    CHECK(hal.stream.type == StreamType_Telnet);
    clear_connection_output();
    uart_output[0] = 0;
    hal.stream.write_all("remaining");
    CHECK(strcmp(primary_output, "remaining") == 0);
    CHECK(strcmp(secondary_output, "remaining") == 0 && uart_output[0] == 0);
    stream_disconnect(&secondary_connection);
    CHECK(stream_get_base() == &usb && hal.stream.state.is_usb);
    CHECK(hal.stream.is_connected() && primary_rt == protocol_enqueue_realtime_command);
    clear_connection_output();
    hal.stream.write("usb reply");
    CHECK(strcmp(primary_output, "usb reply") == 0);
    CHECK(secondary_output[0] == 0 && uart_output[0] == 0);
    return EXIT_SUCCESS;
}
