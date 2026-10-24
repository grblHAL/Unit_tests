#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define GetTickCount windows_GetTickCount
#define Sleep windows_Sleep
#include <windows.h>
#undef GetTickCount
#undef Sleep
#undef NEAR
#else
#include <sys/mman.h>
#endif
#include "sam_host.h"
#include "grbl/state_machine.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
uint32_t SystemCoreClock = 84000000;
const io_stream_t *sam_stream[2];
unsigned sam_clocks, sam_pins, sam_irqs;
static void (*handlers[64])(void);
bool sam_mux_dirty, sam_allow_blocking;
unsigned sam_block_calls, sam_sent_count[2];
uint8_t sam_sent[2][2048];
static bool blocking(void);
void sam_reg_write(const volatile uint32_t *reg, uint32_t value)
{
    CHECK((uintptr_t)reg >= 0x40000000 && (uintptr_t)reg < 0x40400000);
    memcpy((void *)(uintptr_t)reg, &value, 4);
}
void IRQRegister(int32_t irq, void (*handler)(void))
{
    CHECK(irq >= 0 && irq < 64 && handler);
    handlers[irq] = handler;
    sam_irqs++;
}
void IRQUnRegister(int32_t irq)
{
    (void)irq;
    CHECK(false);
}
void NVIC_EnableIRQ(IRQn_Type irq) { CHECK(irq >= 0 && irq < 64 && handlers[irq]); }
void NVIC_SetPriority(IRQn_Type irq, uint32_t priority)
{
    CHECK(irq >= 0 && irq < 64 && priority == 1);
}
uint32_t pmc_enable_periph_clk(uint32_t id)
{
    CHECK(id == ID_UART || id == ID_USART0 || id == ID_USART1 || id == ID_USART2 || id == ID_PIOA ||
          id == ID_PIOB);
    sam_clocks++;
    return 0;
}
static void pin(const periph_pin_t *p)
{
    CHECK(p && (p->function == Input_RX || p->function == Output_TX));
    sam_pins++;
}
void sam_sync(void)
{
    sam_reg_write(&UART->UART_IMR, (UART->UART_IMR | UART->UART_IER) & ~UART->UART_IDR);
    UART->UART_IER = UART->UART_IDR = 0;
    Usart *ports[] = {USART0, USART1, USART2};
    for (unsigned i = 0; i < 3; i++)
    {
        sam_reg_write(&ports[i]->US_IMR, (ports[i]->US_IMR | ports[i]->US_IER) & ~ports[i]->US_IDR);
        ports[i]->US_IER = ports[i]->US_IDR = 0;
    }
}
void sam_prepare(void)
{
#ifdef _WIN32
    void *region =
        VirtualAlloc((void *)0x40000000, 0x400000, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
    void *region = mmap((void *)0x40000000, 0x400000, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
#endif
    CHECK(region == (void *)0x40000000);
    memset(region, 0, 0x400000);
    hal.periph_port.register_pin = pin;
    hal.stream_blocking_callback = blocking;
    if (sam_mux_dirty)
    {
        PIOA->PIO_ABSR = (1U << 12) | (1U << 13) | (1U << 5);
        PIOB->PIO_ABSR = (1U << 20) | (1U << 21) | (1U << 6);
    }
    sam_reg_write(&UART->UART_SR, UART_SR_TXEMPTY);
    sam_reg_write(&USART1->US_CSR, US_CSR_TXEMPTY);
    sam_reg_write(&USART2->US_CSR, US_CSR_TXEMPTY);
    serialRegisterStreams();
    sam_stream[0] = stream_open_instance(0, 115200, NULL, "Host UART");
    sam_stream[1] = stream_open_instance(1, 57600, NULL, "Host UART2");
    CHECK(sam_stream[0] && sam_stream[1]);
    sam_sync();
}
bool protocol_enqueue_realtime_command(uint8_t c) { return c == '!'; }
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
void report_message(const char *text, message_type_t type)
{
    (void)text;
    (void)type;
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

static Usart *usart(unsigned instance)
{
    CHECK(instance < 2);
    return instance == 1 ? USART2 : USART1;
}
static IRQn_Type irq_number(unsigned instance)
{
#if SERIAL_PORT < 0
    if (!instance)
        return UART_IRQn;
#endif
    return instance == 1 ? USART2_IRQn : USART1_IRQn;
}
static bool primary_uart(unsigned instance) { return SERIAL_PORT < 0 && instance == 0; }
void sam_busy(unsigned instance, bool busy)
{
    if (primary_uart(instance))
        sam_reg_write(&UART->UART_SR, busy ? 0 : UART_SR_TXEMPTY);
    else
        sam_reg_write(&usart(instance)->US_CSR, busy ? 0 : US_CSR_TXEMPTY);
}
uint32_t sam_irq_mask(unsigned instance)
{
    return primary_uart(instance) ? UART->UART_IMR : usart(instance)->US_IMR;
}
void sam_mask_clear(unsigned instance)
{
    if (primary_uart(instance))
        sam_reg_write(&UART->UART_IMR, 0);
    else
        sam_reg_write(&usart(instance)->US_IMR, 0);
}
uint32_t sam_last_tx(unsigned instance)
{
    return primary_uart(instance) ? UART->UART_THR : usart(instance)->US_THR;
}
void sam_receive(unsigned instance, uint8_t data)
{
    CHECK(instance < 2);
    sam_sync();
    CHECK(sam_irq_mask(instance) & US_IMR_RXRDY);
    if (primary_uart(instance))
    {
        sam_reg_write(&UART->UART_RHR, data);
        sam_reg_write(&UART->UART_SR, UART_SR_RXRDY | UART_SR_TXEMPTY);
    }
    else
    {
        sam_reg_write(&usart(instance)->US_RHR, data);
        sam_reg_write(&usart(instance)->US_CSR, US_CSR_RXRDY | US_CSR_TXEMPTY);
    }
    CHECK(handlers[irq_number(instance)]);
    handlers[irq_number(instance)]();
    sam_busy(instance, false);
    sam_sync();
}
void sam_transmit(unsigned instance)
{
    CHECK(instance < 2);
    sam_sync();
    CHECK(sam_irq_mask(instance) & US_IMR_TXRDY);
    if (primary_uart(instance))
        sam_reg_write(&UART->UART_SR, UART_SR_TXRDY);
    else
        sam_reg_write(&usart(instance)->US_CSR, US_CSR_TXRDY);
    handlers[irq_number(instance)]();
    CHECK(sam_sent_count[instance] < 2048);
    sam_sent[instance][sam_sent_count[instance]++] = sam_last_tx(instance);
    sam_busy(instance, false);
    sam_sync();
}
void sam_drain(unsigned instance)
{
    sam_busy(instance, false);
    while (sam_stream[instance]->get_tx_buffer_count())
    {
        CHECK(sam_sent_count[instance] < 2048);
        sam_transmit(instance);
    }
}
static bool blocking(void)
{
    CHECK(++sam_block_calls < 10000);
    if (!sam_allow_blocking)
        return false;
    sam_sync();
    for (unsigned i = 0; i < 2; i++)
        if (sam_irq_mask(i) & US_IMR_TXRDY)
            sam_transmit(i);
    return true;
}
