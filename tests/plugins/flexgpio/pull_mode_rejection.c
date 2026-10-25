#include "flex_host.h"
int main(void)
{
    flex_start();
    xbar_t pin = flex_pin(Port_Input, 0);
    gpio_in_config_t cfg = {.pull_mode = PullMode_UpDown};
    CHECK(!pin.config(&pin, &cfg, false));
    return 0;
}
