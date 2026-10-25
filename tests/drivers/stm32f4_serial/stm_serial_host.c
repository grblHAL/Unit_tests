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
#include "stm_serial_host.h"
#include "grbl/state_machine.h"
grbl_hal_t hal;
grbl_t grbl;
system_t sys;
settings_t settings;
parser_state_t gc_state;
const io_stream_t *stm_stream;
unsigned stm_gpio_calls, stm_irq_calls;
GPIO_InitTypeDef stm_gpio_config;
GPIO_TypeDef *stm_gpio_port;
unsigned stm_rt_calls, stm_block_calls;
bool stm_allow_blocking;
uint8_t stm_sent[1024];
size_t stm_sent_count;
const io_stream_t *stm_port_stream[3];
GPIO_InitTypeDef stm_gpio_configs[3];
GPIO_TypeDef *stm_gpio_ports[3];
periph_pin_t stm_registered_pins[6];
unsigned stm_pin_count;
uint8_t stm_port_sent[3][1024];
size_t stm_port_sent_count[3];
void USART1_IRQHandler(void);
#if STM_TRIPLEX
void USART3_IRQHandler(void);
void USART6_IRQHandler(void);
#endif
void HAL_GPIO_Init(GPIO_TypeDef *port, GPIO_InitTypeDef *config)
{
    CHECK(port && config);
    CHECK(stm_gpio_calls < 3);
    stm_gpio_configs[stm_gpio_calls] = *config;
    stm_gpio_ports[stm_gpio_calls++] = port;
    stm_gpio_port = port;
    stm_gpio_config = *config;
}
void HAL_NVIC_SetPriority(IRQn_Type irq, uint32_t preempt, uint32_t sub)
{
    CHECK((irq == USART1_IRQn || irq == USART3_IRQn || irq == USART6_IRQn) && preempt == 1 &&
          sub == 0);
}
void HAL_NVIC_EnableIRQ(IRQn_Type irq)
{
    CHECK(irq == USART1_IRQn || irq == USART3_IRQn || irq == USART6_IRQn);
    stm_irq_calls++;
}
uint32_t HAL_RCC_GetPCLK1Freq(void) { return 42000000; }
uint32_t HAL_RCC_GetPCLK2Freq(void) { return 84000000; }
static bool block(void)
{
    CHECK(++stm_block_calls < 1000);
    if (stm_allow_blocking)
    {
#if STM_TRIPLEX
        USART_TypeDef *ports[] = {USART1, USART3, USART6};
        for (unsigned n = 0; n < 3; n++)
            if (ports[n]->CR1 & USART_CR1_TXEIE)
                stm_transmit_port(n);
#else
        stm_transmit();
#endif
    }
    return stm_allow_blocking;
}
static void pin(const periph_pin_t *info)
{
    CHECK(info && (info->function == Input_RX || info->function == Output_TX));
    CHECK(stm_pin_count < 6);
    memcpy(&stm_registered_pins[stm_pin_count++], info, sizeof(*info));
}
bool protocol_enqueue_realtime_command(uint8_t data)
{
    stm_rt_calls++;
    return data == '!';
}
void stm_serial_prepare(void)
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
    USART1->SR = USART3->SR = USART6->SR = USART_SR_TXE | USART_SR_TC;
    hal.periph_port.register_pin = pin;
    hal.stream_blocking_callback = block;
    serialRegisterStreams();
    stm_stream = stream_open_instance(0, 115200, NULL, "Host UART");
    CHECK(stm_stream);
}
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

static USART_TypeDef *port(unsigned instance)
{
#if STM_TRIPLEX
    USART_TypeDef *ports[] = {USART1, USART3, USART6};
    CHECK(instance < 3);
    return ports[instance];
#else
    CHECK(instance == 0);
    return USART1;
#endif
}
static void deliver(unsigned instance)
{
#if STM_TRIPLEX
    void (*handlers[])(void) = {USART1_IRQHandler, USART3_IRQHandler, USART6_IRQHandler};
    CHECK(instance < 3);
    handlers[instance]();
#else
    CHECK(instance == 0);
    USART1_IRQHandler();
#endif
}
void stm_triplex_prepare(void)
{
    stm_serial_prepare();
    stm_port_stream[0] = stm_stream;
    stm_port_stream[1] = stream_open_instance(1, 57600, NULL, "Host UART2");
    stm_port_stream[2] = stream_open_instance(2, 38400, NULL, "Host UART3");
    CHECK(stm_port_stream[1] && stm_port_stream[2]);
}
void stm_receive_port(unsigned instance, uint8_t data)
{
    USART_TypeDef *device = port(instance);
    CHECK(device->CR1 & USART_CR1_RXNEIE);
    device->DR = data;
    device->SR = USART_SR_RXNE | USART_SR_TC;
    deliver(instance);
    device->SR = USART_SR_TXE | USART_SR_TC;
}
void stm_receive(uint8_t data) { stm_receive_port(0, data); }
void stm_transmit_port(unsigned instance)
{
    USART_TypeDef *device = port(instance);
    CHECK(device->CR1 & USART_CR1_TXEIE);
    device->SR = USART_SR_TXE;
    deliver(instance);
    CHECK(stm_port_sent_count[instance] < sizeof(stm_port_sent[instance]));
    stm_port_sent[instance][stm_port_sent_count[instance]++] = device->DR;
    if (instance == 0)
    {
        CHECK(stm_sent_count < sizeof(stm_sent));
        stm_sent[stm_sent_count++] = device->DR;
    }
    device->SR = USART_SR_TXE | USART_SR_TC;
}
void stm_transmit(void) { stm_transmit_port(0); }
void stm_drain_port(unsigned instance)
{
    while (port(instance)->CR1 & USART_CR1_TXEIE)
        stm_transmit_port(instance);
    const io_stream_t *stream = stm_port_stream[instance];
    if (!instance && !stream)
        stream = stm_stream;
    CHECK(stream && stream->get_tx_buffer_count() == 0);
}
void stm_drain(void) { stm_drain_port(0); }
