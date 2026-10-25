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
#include "stm1_serial_host.h"
#include "grbl/state_machine.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
const io_stream_t *stm1_stream;
unsigned stm1_gpio_calls, stm1_irq_calls, stm1_block_calls, stm1_rt_calls;
GPIO_InitTypeDef stm1_gpio_config;
GPIO_TypeDef *stm1_gpio_port;
GPIO_InitTypeDef stm1_gpio_configs[2];
bool stm1_allow_blocking;
uint8_t stm1_sent[1024];
size_t stm1_sent_count;
void USART1_IRQHandler(void);
void HAL_GPIO_Init(GPIO_TypeDef *port, GPIO_InitTypeDef *config)
{
    CHECK(port && config);
    CHECK(stm1_gpio_calls < 2);
    stm1_gpio_configs[stm1_gpio_calls++] = *config;
    stm1_gpio_port = port;
    stm1_gpio_config = *config;
}
void HAL_NVIC_SetPriority(IRQn_Type irq, uint32_t preempt, uint32_t sub)
{
    CHECK(irq == USART1_IRQn && preempt == 1 && sub == 0);
}
void HAL_NVIC_EnableIRQ(IRQn_Type irq)
{
    CHECK(irq == USART1_IRQn);
    stm1_irq_calls++;
}
uint32_t HAL_RCC_GetPCLK1Freq(void) { return 36000000; }
uint32_t HAL_RCC_GetPCLK2Freq(void) { return 72000000; }
static bool block(void)
{
    CHECK(++stm1_block_calls < 1000);
    if (stm1_allow_blocking)
        stm1_transmit();
    return stm1_allow_blocking;
}
static void pin(const periph_pin_t *info)
{
    CHECK(info && (info->function == Input_RX || info->function == Output_TX));
}
bool protocol_enqueue_realtime_command(uint8_t data)
{
    stm1_rt_calls++;
    return data == '!';
}
void stm1_prepare(void)
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
    USART1->SR = USART_SR_TXE | USART_SR_TC;
    hal.periph_port.register_pin = pin;
    hal.stream_blocking_callback = block;
    serialRegisterStreams();
    stm1_stream = stream_open_instance(0, 115200, NULL, "Host UART");
    CHECK(stm1_stream);
}
void stm1_receive(uint8_t data)
{
    CHECK(USART1->CR1 & USART_CR1_RXNEIE);
    USART1->DR = data;
    USART1->SR = USART_SR_RXNE | USART_SR_TC;
    USART1_IRQHandler();
    USART1->SR = USART_SR_TXE | USART_SR_TC;
}
void stm1_transmit(void)
{
    CHECK(USART1->CR1 & USART_CR1_TXEIE);
    USART1->SR = USART_SR_TXE;
    USART1_IRQHandler();
    CHECK(stm1_sent_count < sizeof(stm1_sent));
    stm1_sent[stm1_sent_count++] = USART1->DR;
    USART1->SR = USART_SR_TXE | USART_SR_TC;
}
void stm1_drain(void)
{
    while (USART1->CR1 & USART_CR1_TXEIE)
        stm1_transmit();
}
