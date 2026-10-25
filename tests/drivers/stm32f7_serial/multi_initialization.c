#include "stm7_serial_host.h"
int main(void)
{
    stm7_triplex_prepare();
    CHECK(stm7_gpio_calls == 3 && stm7_irq_calls == 3 && stm7_pin_count == 6);
    GPIO_TypeDef *ports[] = {GPIOD, GPIOC, GPIOA};
    const uint32_t pins[] = {GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_6 | GPIO_PIN_7,
                             GPIO_PIN_9 | GPIO_PIN_10};
    const uint32_t alternate[] = {GPIO_AF7_USART3, GPIO_AF8_USART6, GPIO_AF7_USART1};
    const uint32_t baud[] = {115200, 57600, 38400};
    for (unsigned n = 0; n < 3; n++)
    {
        CHECK(stm7_gpio_ports[n] == ports[n] && stm7_gpio_configs[n].Pin == pins[n]);
        CHECK(stm7_gpio_configs[n].Alternate == alternate[n] &&
              stm7_gpio_configs[n].Mode == GPIO_MODE_AF_PP);
        CHECK(stream_get_uart_status(n)->baud_rate == baud[n]);
        CHECK(stm7_port_stream[n]->get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    }
    CHECK((RCC->APB2ENR & (RCC_APB2ENR_USART1EN | RCC_APB2ENR_USART6EN)) ==
          (RCC_APB2ENR_USART1EN | RCC_APB2ENR_USART6EN));
    CHECK(RCC->APB1ENR & RCC_APB1ENR_USART3EN);
    return 0;
}
