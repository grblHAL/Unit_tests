#include "stm3_serial_host.h"
int main(void)
{
    stm3_prepare();
    CHECK(stm3_gpio_calls == 1 && stm3_irq_calls == 1 && stm3_gpio_port == GPIOB);
    CHECK(stm3_gpio_config.Pin == (GPIO_PIN_10 | GPIO_PIN_11));
    CHECK(stm3_gpio_config.Mode == GPIO_MODE_AF_PP &&
          stm3_gpio_config.Alternate == GPIO_AF7_USART3);
    CHECK(RCC->APB1ENR & RCC_APB1ENR_USART3EN);
    CHECK(RCC->AHBENR & RCC_AHBENR_GPIOBEN);
    CHECK(stream_get_uart_status(0)->baud_rate == 115200 &&
          !stream_get_uart_status(0)->flags.can_set_baud);
    CHECK(stm3_stream->read() == SERIAL_NO_DATA && !stm3_stream->set_baud_rate &&
          !stm3_stream->set_format);
    return 0;
}
