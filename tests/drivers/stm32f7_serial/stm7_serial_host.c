#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define GetTickCount windows_GetTickCount
#define Sleep windows_Sleep
#include <windows.h>
#undef GetTickCount
#undef Sleep
#undef NEAR
#undef ERROR
#undef LPTR
#else
#include <sys/mman.h>
#endif
#include "stm7_serial_host.h"
#include "grbl/state_machine.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
const io_stream_t *stm7_stream;
unsigned stm7_gpio_calls, stm7_irq_calls;
GPIO_InitTypeDef stm7_gpio_config;
GPIO_TypeDef *stm7_gpio_port;
unsigned stm7_rt_calls, stm7_block_calls;
bool stm7_allow_blocking;
uint8_t stm7_sent[1024];
size_t stm7_sent_count;
const io_stream_t *stm7_port_stream[3];
GPIO_InitTypeDef stm7_gpio_configs[3];
GPIO_TypeDef *stm7_gpio_ports[3];
periph_pin_t stm7_registered_pins[6];
unsigned stm7_pin_count;
uint8_t stm7_port_sent[3][1024];
size_t stm7_port_sent_count[3];
void USART3_IRQHandler(void);
#if STM_TRIPLEX
void USART1_IRQHandler(void);
void USART6_IRQHandler(void);
#endif
void HAL_GPIO_Init(GPIO_TypeDef *port, GPIO_InitTypeDef *config)
{
    CHECK(port && config);
    CHECK(stm7_gpio_calls < 3);
    stm7_gpio_configs[stm7_gpio_calls] = *config;
    stm7_gpio_ports[stm7_gpio_calls++] = port;
    stm7_gpio_port = port;
    stm7_gpio_config = *config;
}
void HAL_NVIC_SetPriority(IRQn_Type irq, uint32_t preempt, uint32_t sub)
{
    CHECK((irq == USART1_IRQn || irq == USART3_IRQn || irq == USART6_IRQn) && preempt == 1 &&
          sub == 0);
}
void HAL_NVIC_EnableIRQ(IRQn_Type irq)
{
    CHECK(irq == USART1_IRQn || irq == USART3_IRQn || irq == USART6_IRQn);
    stm7_irq_calls++;
}
uint32_t HAL_RCC_GetPCLK1Freq(void) { return 54000000; }
uint32_t HAL_RCC_GetPCLK2Freq(void) { return 108000000; }
static bool block(void)
{
    CHECK(++stm7_block_calls < 1000);
    if (stm7_allow_blocking)
    {
#if STM_TRIPLEX
        USART_TypeDef *ports[] = {USART3, USART6, USART1};
        for (unsigned n = 0; n < 3; n++)
            if (ports[n]->CR1 & USART_CR1_TXEIE)
                stm7_transmit_port(n);
#else
        stm7_transmit();
#endif
    }
    return stm7_allow_blocking;
}
static void pin(const periph_pin_t *info)
{
    CHECK(info && (info->function == Input_RX || info->function == Output_TX));
    CHECK(stm7_pin_count < 6);
    memcpy(&stm7_registered_pins[stm7_pin_count++], info, sizeof(*info));
}
bool protocol_enqueue_realtime_command(uint8_t data)
{
    stm7_rt_calls++;
    return data == '!';
}
void stm7_prepare(void)
{
#ifdef _WIN32
    void *region =
        VirtualAlloc((void *)0x40000000, 0x40000, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
    void *region = mmap((void *)0x40000000, 0x40000, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
#endif
    CHECK(region == (void *)0x40000000);
    memset(region, 0, 0x40000);
    USART1->ISR = USART3->ISR = USART6->ISR = USART_ISR_TXE | USART_ISR_TC;
    hal.periph_port.register_pin = pin;
    hal.stream_blocking_callback = block;
    serialRegisterStreams();
    stm7_stream = stream_open_instance(0, 115200, NULL, "Host UART");
    CHECK(stm7_stream);
}
static USART_TypeDef *port(unsigned instance)
{
#if STM_TRIPLEX
    USART_TypeDef *ports[] = {USART3, USART6, USART1};
    CHECK(instance < 3);
    return ports[instance];
#else
    CHECK(instance == 0);
    return USART3;
#endif
}
static void deliver(unsigned instance)
{
#if STM_TRIPLEX
    void (*handlers[])(void) = {USART3_IRQHandler, USART6_IRQHandler, USART1_IRQHandler};
    CHECK(instance < 3);
    handlers[instance]();
#else
    CHECK(instance == 0);
    USART3_IRQHandler();
#endif
}
void stm7_triplex_prepare(void)
{
    stm7_prepare();
    stm7_port_stream[0] = stm7_stream;
    stm7_port_stream[1] = stream_open_instance(1, 57600, NULL, "Host UART2");
    stm7_port_stream[2] = stream_open_instance(2, 38400, NULL, "Host UART3");
    CHECK(stm7_port_stream[1] && stm7_port_stream[2]);
}
void stm7_receive_port(unsigned instance, uint8_t data)
{
    USART_TypeDef *device = port(instance);
    CHECK(device->CR1 & USART_CR1_RXNEIE);
    device->RDR = data;
    device->ISR = USART_ISR_RXNE | USART_ISR_TC;
    deliver(instance);
    device->ISR = USART_ISR_TXE | USART_ISR_TC;
}
void stm7_receive(uint8_t data) { stm7_receive_port(0, data); }
void stm7_transmit_port(unsigned instance)
{
    USART_TypeDef *device = port(instance);
    CHECK(device->CR1 & USART_CR1_TXEIE);
    device->ISR = USART_ISR_TXE;
    deliver(instance);
    CHECK(stm7_port_sent_count[instance] < sizeof(stm7_port_sent[instance]));
    stm7_port_sent[instance][stm7_port_sent_count[instance]++] = device->TDR;
    if (instance == 0)
    {
        CHECK(stm7_sent_count < sizeof(stm7_sent));
        stm7_sent[stm7_sent_count++] = device->TDR;
    }
    device->ISR = USART_ISR_TXE | USART_ISR_TC;
}
void stm7_transmit(void) { stm7_transmit_port(0); }
void stm7_drain_port(unsigned instance)
{
    while (port(instance)->CR1 & USART_CR1_TXEIE)
        stm7_transmit_port(instance);
    const io_stream_t *stream = stm7_port_stream[instance];
    if (!instance && !stream)
        stream = stm7_stream;
    CHECK(stream && stream->get_tx_buffer_count() == 0);
}
void stm7_drain(void) { stm7_drain_port(0); }
