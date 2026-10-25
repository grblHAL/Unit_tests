#include "psoc_host.h"
#ifdef LEGACY_CORE_STREAM
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
#endif
const io_stream_t *psoc_stream;
unsigned starts, rt_calls, clears, sent_count;
uint8_t sent[256];
static uint8_t fifo[256];
static size_t head, tail;
static void (*irq)(void);
void UART_Start(void) { starts++; }
void UART_RX_Interrupt_StartEx(void (*handler)(void))
{
    CHECK(handler && !irq);
    irq = handler;
}
void UART_PutChar(uint8_t value)
{
    CHECK(sent_count < sizeof(sent));
    sent[sent_count++] = value;
}
uint8_t UART_GetChar(void) { return tail == head ? 0 : fifo[tail++]; }
void UART_ClearRxBuffer(void)
{
    tail = head;
    clears++;
}
bool protocol_enqueue_realtime_command(char value)
{
    rt_calls++;
    return value == '!';
}
#ifndef LEGACY_CORE_STREAM
bool stream_connected(void) { return true; }
bool stream_rx_suspend(stream_rx_buffer_t *buffer, bool suspend)
{
    (void)buffer;
    (void)suspend;
    CHECK(false);
    return false;
}
#endif
void psoc_start(void)
{
    psoc_stream = serialInit();
    CHECK(psoc_stream && starts == 1 && irq);
}
void psoc_receive(const uint8_t *data, size_t size)
{
    CHECK(irq && head == tail && size <= sizeof(fifo));
    for (size_t i = 0; i < size; i++)
        CHECK(data[i] != 0);
    memcpy(fifo, data, size);
    head = size;
    tail = 0;
    irq();
    CHECK(head == tail);
}
