#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#undef IN
#undef OUT
#undef NEAR
#else
#include <sys/mman.h>
#endif
#include "msp_host.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
const io_stream_t *msp_stream;
unsigned pins, rt_calls, blocks, sent_count, irq_enables, irq_disables;
bool allow_blocking, cpu_enabled = true;
uint8_t sent[2048];
uint32_t now;
void msp_irq_enable(void)
{
    cpu_enabled = true;
    irq_enables++;
}
void msp_irq_disable(void)
{
    CHECK(cpu_enabled);
    cpu_enabled = false;
    irq_disables++;
}
static void own_region(uintptr_t base, size_t size)
{
#ifdef _WIN32
    void *p = VirtualAlloc((void *)base, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
    void *p = mmap((void *)base, size, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
#endif
    CHECK(p == (void *)base);
    memset(p, 0, size);
}
void msp_map(void)
{
    own_region(0x40000000, 0x10000);
    own_region(0xE0000000, 0x10000);
}
static void hardware16(const volatile uint16_t *reg, uint16_t value)
{
    CHECK((uintptr_t)reg >= 0x40000000 && (uintptr_t)reg < 0x40010000);
    memcpy((void *)(uintptr_t)reg, &value, 2);
}
static void pin(const periph_pin_t *p)
{
    CHECK(p && p->group == PinGroup_UART && p->port == P1);
    CHECK((p->function == Input_RX && p->pin == 2) || (p->function == Output_TX && p->pin == 3));
    pins++;
}
static uint32_t ticks(void) { return now; }
bool protocol_enqueue_realtime_command(uint8_t value)
{
    rt_calls++;
    return value == '!' || value == CMD_STATUS_REPORT_LEGACY || value == CMD_STATUS_REPORT;
}
static bool blocking(void)
{
    CHECK(++blocks < 10000);
    if (!allow_blocking)
        return false;
    msp_transmit();
    return true;
}
void msp_start(void)
{
    msp_map();
    hal.periph_port.register_pin = pin;
    hal.get_elapsed_ticks = ticks;
    hal.stream_blocking_callback = blocking;
    serialRegisterStreams();
    msp_stream = stream_open_instance(0, 115200, NULL, "MSP host UART");
    CHECK(msp_stream);
}
void msp_receive(uint8_t value)
{
    CHECK(EUSCI_A0->IE & EUSCI_A_IE_RXIE);
    hardware16(&EUSCI_A0->RXBUF, value);
    hardware16(&EUSCI_A0->IV, 2);
    EUSCIA0_IRQHandler();
}
void msp_busy(bool busy) { hardware16(&EUSCI_A0->STATW, busy ? EUSCI_A_STATW_BUSY : 0); }
void msp_transmit(void)
{
    CHECK(EUSCI_A0->IE & EUSCI_A_IE_TXIE);
    hardware16(&EUSCI_A0->IV, 4);
    EUSCIA0_IRQHandler();
    CHECK(sent_count < sizeof(sent));
    sent[sent_count++] = (uint8_t)EUSCI_A0->TXBUF;
    msp_busy(false);
}
void msp_drain(void)
{
    while (EUSCI_A0->IE & EUSCI_A_IE_TXIE)
        msp_transmit();
}
