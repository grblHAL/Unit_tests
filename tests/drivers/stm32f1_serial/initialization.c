#include "stm1_serial_host.h"
int main(void)
{
    stm1_prepare();
    CHECK(stm1_gpio_calls == 2 && stm1_irq_calls == 1 && stm1_gpio_port == GPIOA);
    CHECK(stm1_gpio_configs[0].Pin == GPIO_PIN_9 && stm1_gpio_configs[0].Mode == GPIO_MODE_AF_PP);
    CHECK(stm1_gpio_configs[1].Pin == GPIO_PIN_10 && stm1_gpio_configs[1].Mode == GPIO_MODE_INPUT);
    CHECK(RCC->APB2ENR & RCC_APB2ENR_USART1EN);
    CHECK(stream_get_uart_status(0)->baud_rate == 115200 &&
          stream_get_uart_status(0)->flags.can_set_baud);
    CHECK(stm1_stream->read() == SERIAL_NO_DATA && !stm1_stream->set_format);
    return 0;
}
