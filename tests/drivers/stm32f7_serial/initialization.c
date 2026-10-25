#include "stm7_serial_host.h"
int main(void)
{
    stm7_prepare();
    CHECK(stm7_gpio_calls == 1 && stm7_irq_calls == 1 && stm7_gpio_port == GPIOD);
    CHECK(stm7_gpio_config.Pin == (GPIO_PIN_8 | GPIO_PIN_9));
    CHECK(stm7_gpio_config.Mode == GPIO_MODE_AF_PP &&
          stm7_gpio_config.Alternate == GPIO_AF7_USART3);
    CHECK(RCC->APB1ENR & RCC_APB1ENR_USART3EN);
    CHECK((USART3->CR1 & (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE | USART_CR1_RXNEIE)) ==
          (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE | USART_CR1_RXNEIE));
    CHECK(USART3->CR3 == USART_CR3_OVRDIS);
    CHECK(stream_get_uart_status(0)->baud_rate == 115200);
    CHECK(stm7_stream->read() == SERIAL_NO_DATA &&
          stm7_stream->get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    CHECK(!stream_open_instance(0, 9600, NULL, NULL));
    return 0;
}
