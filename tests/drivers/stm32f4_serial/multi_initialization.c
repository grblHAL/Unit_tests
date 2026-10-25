#include "stm_serial_host.h"
int main(void)
{
    stm_triplex_prepare();
    CHECK(stm_gpio_calls == 3 && stm_irq_calls == 3 && stm_pin_count == 6);
    GPIO_TypeDef *ports[] = {GPIOA, GPIOB, GPIOC};
    const uint32_t pins[] = {GPIO_PIN_9 | GPIO_PIN_10, GPIO_PIN_10 | GPIO_PIN_11,
                             GPIO_PIN_6 | GPIO_PIN_7};
    const uint32_t alternate[] = {GPIO_AF7_USART1, GPIO_AF7_USART3, GPIO_AF8_USART6};
    const uint32_t baud[] = {115200, 57600, 38400};
    for (unsigned n = 0; n < 3; n++)
    {
        CHECK(stm_gpio_ports[n] == ports[n] && stm_gpio_configs[n].Pin == pins[n]);
        CHECK(stm_gpio_configs[n].Alternate == alternate[n] &&
              stm_gpio_configs[n].Mode == GPIO_MODE_AF_PP);
        CHECK(stream_get_uart_status(n)->baud_rate == baud[n]);
        CHECK(stm_port_stream[n]->get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    }
    CHECK((RCC->APB2ENR & (RCC_APB2ENR_USART1EN | RCC_APB2ENR_USART6EN)) ==
          (RCC_APB2ENR_USART1EN | RCC_APB2ENR_USART6EN));
    CHECK(RCC->APB1ENR & RCC_APB1ENR_USART3EN);
    return 0;
}
