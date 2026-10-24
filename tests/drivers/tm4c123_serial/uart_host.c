#include "uart_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
const io_stream_t *uart_stream;
unsigned pins, clocks, rt_calls, block_calls, tx_count;
bool tx_ready = true, allow_blocking, rts;
uint8_t tx_data[4096];
uint32_t irq_mask;
static uint32_t pending;
static uint8_t received;
static void (*handler)(void);
static void check_uart(uint32_t base) { CHECK(base == UART0_BASE); }
void SysCtlPeripheralEnable(uint32_t periph)
{
    CHECK(periph == SYSCTL_PERIPH_GPIOA || periph == SYSCTL_PERIPH_UART0);
    clocks++;
}
void SysCtlDelay(uint32_t count) { CHECK(count == 3); }
void GPIOPinConfigure(uint32_t config)
{
    CHECK(config == GPIO_PA0_U0RX || config == GPIO_PA1_U0TX);
}
void GPIOPinTypeUART(uint32_t port, uint8_t mask)
{
    CHECK(port == GPIO_PORTA_BASE && mask == (GPIO_PIN_0 | GPIO_PIN_1));
}
void GPIOPinWrite(uint32_t port, uint8_t mask, uint8_t value)
{
    CHECK(port == RTS_PORT && mask == RTS_PIN && (value == 0 || value == RTS_PIN));
    rts = value != 0;
}
void UARTClockSourceSet(uint32_t base, uint32_t source)
{
    check_uart(base);
    CHECK(source == UART_CLOCK_PIOSC);
}
void UARTConfigSetExpClk(uint32_t base, uint32_t clock, uint32_t baud, uint32_t config)
{
    check_uart(base);
    CHECK(clock == 16000000 && baud == 115200 &&
          config == (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}
void UARTFIFOEnable(uint32_t base) { check_uart(base); }
void UARTFIFOLevelSet(uint32_t base, uint32_t tx, uint32_t rx)
{
    check_uart(base);
    CHECK(tx == UART_FIFO_TX1_8 && rx == UART_FIFO_RX1_8);
}
void IntPrioritySet(uint32_t irq, uint8_t priority) { CHECK(irq == INT_UART0 && priority == 0x40); }
void UARTIntRegister(uint32_t base, void (*fn)(void))
{
    check_uart(base);
    CHECK(fn);
    handler = fn;
}
void UARTIntEnable(uint32_t base, uint32_t flags)
{
    check_uart(base);
    irq_mask |= flags;
}
void UARTIntDisable(uint32_t base, uint32_t flags)
{
    check_uart(base);
    irq_mask &= ~flags;
}
void UARTTxIntModeSet(uint32_t base, uint32_t mode)
{
    check_uart(base);
    CHECK(mode == UART_TXINT_MODE_EOT);
}
void UARTEnable(uint32_t base) { check_uart(base); }
uint32_t UARTIntStatus(uint32_t base, bool masked)
{
    check_uart(base);
    return masked ? pending & irq_mask : pending;
}
int32_t UARTCharGet(uint32_t base)
{
    check_uart(base);
    CHECK(pending & (UART_INT_RX | UART_INT_RT));
    pending &= ~(UART_INT_RX | UART_INT_RT);
    return received;
}
void UARTCharPut(uint32_t base, unsigned char value)
{
    check_uart(base);
    CHECK(tx_ready && tx_count < sizeof(tx_data));
    tx_data[tx_count++] = value;
}
bool UARTCharPutNonBlocking(uint32_t base, unsigned char value)
{
    check_uart(base);
    if (!tx_ready)
        return false;
    UARTCharPut(base, value);
    return true;
}
bool UARTSpaceAvail(uint32_t base)
{
    check_uart(base);
    return tx_ready;
}
static void pin(const periph_pin_t *p)
{
    CHECK(p && p->group == PinGroup_UART && p->port == (void *)GPIO_PORTA_BASE);
    CHECK((p->pin == 0 && p->function == Input_RX) || (p->pin == 1 && p->function == Output_TX));
    pins++;
}
bool protocol_enqueue_realtime_command(uint8_t value)
{
    rt_calls++;
    return value == '!';
}
static bool blocking(void)
{
    CHECK(++block_calls < 100);
    if (!allow_blocking)
        return false;
    tx_ready = true;
    pending = UART_INT_TX;
    CHECK(handler);
    handler();
    return true;
}
void uart_start(void)
{
    hal.periph_port.register_pin = pin;
    hal.stream_blocking_callback = blocking;
    uart_stream = serialInit();
    CHECK(uart_stream && handler);
}
void uart_receive(uint8_t value)
{
    CHECK(handler && (irq_mask & UART_INT_RX));
    received = value;
    pending = UART_INT_RX;
    handler();
}
void uart_drain(void)
{
    tx_ready = true;
    while (uart_stream->get_tx_buffer_count())
    {
        CHECK(irq_mask & UART_INT_TX);
        pending = UART_INT_TX;
        handler();
    }
}
