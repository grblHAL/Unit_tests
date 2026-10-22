#include "support/mpg_input_settings_host.h"
int main(void)
{
    prepare_mpg_input_settings(0, PullMode_Down);
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 1);
    CHECK(captured_input[1].inverted && captured_input[1].pull_mode == PullMode_Down);
    CHECK(captured_input[0].debounce && !captured_input[0].inverted);
    CHECK(captured_input[0].pull_mode == PullMode_Up);
    return EXIT_SUCCESS;
}
