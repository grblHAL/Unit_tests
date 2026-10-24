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
uint32_t irq_mask, irq_mask2;
static uint32_t pending2;
static uint8_t received2;
#ifdef SERIAL2_MOD
static void (*handler2)(void);
#endif
static uint32_t pending;
static uint8_t received;
static void (*handler)(void);
static unsigned uart_index(uint32_t base)
{
    if (base == UART0_BASE)
        return 0;
#ifdef SERIAL2_MOD
    if (base == UART7_BASE)
        return 1;
#endif
    CHECK(false);
    return 0;
}
static void check_uart(uint32_t base) { (void)uart_index(base); }
void SysCtlPeripheralEnable(uint32_t periph)
{
#ifdef SERIAL2_MOD
    CHECK(periph == SYSCTL_PERIPH_GPIOA || periph == SYSCTL_PERIPH_UART0 ||
          periph == SYSCTL_PERIPH_GPIOC || periph == SYSCTL_PERIPH_UART7);
#else
    CHECK(periph == SYSCTL_PERIPH_GPIOA || periph == SYSCTL_PERIPH_UART0);
#endif
    clocks++;
}
void SysCtlDelay(uint32_t count) { CHECK(count == 3); }
void GPIOPinConfigure(uint32_t config)
{
#ifdef SERIAL2_MOD
    CHECK(config == GPIO_PA0_U0RX || config == GPIO_PA1_U0TX || config == GPIO_PC4_U7RX ||
          config == GPIO_PC5_U7TX);
#else
    CHECK(config == GPIO_PA0_U0RX || config == GPIO_PA1_U0TX);
#endif
}
void GPIOPinTypeUART(uint32_t port, uint8_t mask)
{
#ifdef SERIAL2_MOD
    if (port == GPIO_PORTC_BASE)
    {
        CHECK(mask == (GPIO_PIN_4 | GPIO_PIN_5));
        return;
    }
#endif
    CHECK(port == GPIO_PORTA_BASE && mask == (GPIO_PIN_0 | GPIO_PIN_1));
}
void GPIOPinWrite(uint32_t port, uint8_t mask, uint8_t value)
{
#ifdef TI_SHARED_REFERENCE
    (void)port;
    (void)mask;
    (void)value;
    CHECK(false);
#else
    CHECK(port == RTS_PORT && mask == RTS_PIN && (value == 0 || value == RTS_PIN));
    rts = value != 0;
#endif
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
void IntPrioritySet(uint32_t irq, uint8_t priority)
{
#ifdef SERIAL2_MOD
    CHECK((irq == INT_UART0 || irq == INT_UART7) && priority == 0x40);
#else
    CHECK(irq == INT_UART0 && priority == 0x40);
#endif
}
void UARTIntRegister(uint32_t base, void (*fn)(void))
{
    check_uart(base);
    CHECK(fn);
#ifdef SERIAL2_MOD
    if (uart_index(base))
    {
        handler2 = fn;
        return;
    }
#endif
    handler = fn;
}
void UARTIntEnable(uint32_t base, uint32_t flags)
{
    check_uart(base);
    if (uart_index(base))
        irq_mask2 |= flags;
    else
        irq_mask |= flags;
}
void UARTIntDisable(uint32_t base, uint32_t flags)
{
    check_uart(base);
    if (uart_index(base))
        irq_mask2 &= ~flags;
    else
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
    if (uart_index(base))
        return masked ? pending2 & irq_mask2 : pending2;
    return masked ? pending & irq_mask : pending;
}
int32_t UARTCharGet(uint32_t base)
{
    check_uart(base);
    if (uart_index(base))
    {
        CHECK(pending2 & (UART_INT_RX | UART_INT_RT));
        pending2 &= ~(UART_INT_RX | UART_INT_RT);
        return received2;
    }
    CHECK(pending & (UART_INT_RX | UART_INT_RT));
    pending &= ~(UART_INT_RX | UART_INT_RT);
    return received;
}
void UARTCharPut(uint32_t base, unsigned char value)
{
    check_uart(base);
    CHECK(base == UART0_BASE && tx_ready && tx_count < sizeof(tx_data));
    tx_data[tx_count++] = value;
}
bool UARTCharPutNonBlocking(uint32_t base, unsigned char value)
{
    check_uart(base);
    CHECK(base == UART0_BASE);
    if (!tx_ready)
        return false;
    UARTCharPut(base, value);
    return true;
}
bool UARTSpaceAvail(uint32_t base)
{
    check_uart(base);
    CHECK(base == UART0_BASE);
    return tx_ready;
}
static void pin(const periph_pin_t *p)
{
#ifdef SERIAL2_MOD
    if (p && p->group == PinGroup_UART2)
    {
        CHECK(p->port == (void *)UART7_BASE && ((p->pin == 4 && p->function == Input_RX) ||
                                                (p->pin == 5 && p->function == Output_TX)));
        pins++;
        return;
    }
#endif
#ifdef TI_SHARED_REFERENCE
    CHECK(p && p->group == PinGroup_UART && p->port == (void *)UART0_BASE);
#else
    CHECK(p && p->group == PinGroup_UART && p->port == (void *)GPIO_PORTA_BASE);
#endif
    CHECK((p->pin == 0 && p->function == Input_RX) || (p->pin == 1 && p->function == Output_TX));
    pins++;
}
#ifdef TI_SHARED_REFERENCE
bool protocol_enqueue_realtime_command(char value)
#else
bool protocol_enqueue_realtime_command(uint8_t value)
#endif
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
#ifdef TI_SHARED_REFERENCE
    serialRegisterStreams();
#ifdef LEGACY_CORE_STREAM
    uart_stream = stream_open_instance(0, 115200, NULL, "Legacy host UART");
#else
    uart_stream = serialInit(115200);
#endif
#else
    uart_stream = serialInit();
#endif
    CHECK(uart_stream && handler);
}
void uart_event(uint32_t flags, uint8_t value)
{
    CHECK(handler && flags && (flags & ~(UART_INT_RX | UART_INT_RT | UART_INT_TX)) == 0 &&
          (irq_mask & flags) == flags);
    received = value;
    pending = flags;
    handler();
}
void uart_receive(uint8_t value) { uart_event(UART_INT_RX, value); }
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

#ifdef SERIAL2_MOD
const io_stream_t *uart2_stream;
void uart2_start(void)
{
    uart2_stream = serial2Init(115200);
    CHECK(uart2_stream && handler2);
}
void uart2_event(uint32_t flags, uint8_t value)
{
    CHECK(handler2 && flags && (flags & ~(UART_INT_RX | UART_INT_RT)) == 0 &&
          (irq_mask2 & flags) == flags);
    received2 = value;
    pending2 = flags;
    handler2();
}
#endif
