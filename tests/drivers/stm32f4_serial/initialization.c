#include "stm_serial_host.h"
int main(void)
{
    stm_serial_prepare();
    CHECK(stm_gpio_calls == 1 && stm_irq_calls == 1 && stm_gpio_port == GPIOA);
    CHECK(stm_gpio_config.Pin == (GPIO_PIN_9 | GPIO_PIN_10));
    CHECK(stm_gpio_config.Mode == GPIO_MODE_AF_PP && stm_gpio_config.Alternate == GPIO_AF7_USART1);
    CHECK(RCC->APB2ENR & RCC_APB2ENR_USART1EN);
    CHECK((USART1->CR1 & (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE | USART_CR1_RXNEIE)) ==
          (USART_CR1_RE | USART_CR1_TE | USART_CR1_UE | USART_CR1_RXNEIE));
    CHECK(stream_get_uart_status(0)->baud_rate == 115200);
    CHECK(stm_stream->read() == SERIAL_NO_DATA &&
          stm_stream->get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    CHECK(!stream_open_instance(0, 9600, NULL, NULL));
    return 0;
}
