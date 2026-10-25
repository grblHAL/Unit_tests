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
#else
#include <sys/mman.h>
#endif
#include "stm3_serial_host.h"
#include "grbl/state_machine.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
const io_stream_t *stm3_stream;
unsigned stm3_gpio_calls, stm3_irq_calls, stm3_block_calls, stm3_rt_calls;
GPIO_InitTypeDef stm3_gpio_config;
GPIO_TypeDef *stm3_gpio_port;
bool stm3_allow_blocking;
uint8_t stm3_sent[1024];
size_t stm3_sent_count;
void USART3_IRQHandler(void);
void HAL_GPIO_Init(GPIO_TypeDef *port, GPIO_InitTypeDef *config)
{
    CHECK(port && config);
    stm3_gpio_calls++;
    stm3_gpio_port = port;
    stm3_gpio_config = *config;
}
void HAL_NVIC_SetPriority(IRQn_Type irq, uint32_t preempt, uint32_t sub)
{
    CHECK(irq == USART3_IRQn && preempt == 1 && sub == 0);
}
void HAL_NVIC_EnableIRQ(IRQn_Type irq)
{
    CHECK(irq == USART3_IRQn);
    stm3_irq_calls++;
}
uint32_t HAL_RCC_GetPCLK1Freq(void) { return 36000000; }
static bool block(void)
{
    CHECK(++stm3_block_calls < 1000);
    if (stm3_allow_blocking)
        stm3_transmit();
    return stm3_allow_blocking;
}
static void pin(const periph_pin_t *info)
{
    CHECK(info && (info->function == Input_RX || info->function == Output_TX));
}
bool protocol_enqueue_realtime_command(uint8_t data)
{
    stm3_rt_calls++;
    return data == '!';
}
void stm3_prepare(void)
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
    USART3->ISR = USART_ISR_TXE | USART_ISR_TC;
    hal.periph_port.register_pin = pin;
    hal.stream_blocking_callback = block;
    serialRegisterStreams();
    stm3_stream = stream_open_instance(0, 115200, NULL, "Host UART");
    CHECK(stm3_stream);
}
void stm3_receive(uint8_t data)
{
    CHECK(USART3->CR1 & USART_CR1_RXNEIE);
    USART3->RDR = data;
    USART3->ISR = USART_ISR_RXNE | USART_ISR_TC;
    USART3_IRQHandler();
    USART3->ISR = USART_ISR_TXE | USART_ISR_TC;
}
void stm3_transmit(void)
{
    CHECK(USART3->CR1 & USART_CR1_TXEIE);
    USART3->ISR = USART_ISR_TXE;
    USART3_IRQHandler();
    CHECK(stm3_sent_count < sizeof(stm3_sent));
    stm3_sent[stm3_sent_count++] = USART3->TDR;
    USART3->ISR = USART_ISR_TXE | USART_ISR_TC;
}
void stm3_drain(void)
{
    while (USART3->CR1 & USART_CR1_TXEIE)
        stm3_transmit();
}
