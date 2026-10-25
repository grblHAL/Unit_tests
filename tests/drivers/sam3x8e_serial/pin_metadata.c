#include "sam_host.h"
int main(void)
{
    sam_prepare();
    const int ports[] = {SERIAL_PORT, SERIAL1_PORT};
    CHECK(sam_pins == 4);
    for (unsigned instance = 0; instance < 2; instance++)
    {
        const periph_pin_t *rx = &sam_registered_pins[instance * 2];
        const periph_pin_t *tx = &sam_registered_pins[instance * 2 + 1];
        CHECK(rx->function == Input_RX && tx->function == Output_TX);
        CHECK(rx->group == (instance ? PinGroup_UART2 : PinGroup_UART));
        CHECK(tx->group == rx->group);
        CHECK(rx->port == (ports[instance] == 2 ? PIOB : PIOA) && tx->port == rx->port);
        CHECK(rx->pin == (ports[instance] < 0 ? 8 : ports[instance] == 1 ? 12 : 21));
        CHECK(tx->pin == (ports[instance] < 0 ? 9 : ports[instance] == 1 ? 13 : 20));
        CHECK(tx->mode.output && !rx->mode.output);
        CHECK(strcmp(tx->description, instance ? "Secondary UART" : "Primary UART") == 0);
    }
    return 0;
}
