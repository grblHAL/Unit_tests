#include "support/mpg_input_settings_host.h"
int main(void)
{
    prepare_mpg_input_settings(1, PullMode_Up);
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 1);
    CHECK(captured_input[0].inverted && captured_input[0].pull_mode == PullMode_Up);
    CHECK(captured_input[1].debounce && !captured_input[1].inverted);
    CHECK(captured_input[1].pull_mode == PullMode_Up);
    return EXIT_SUCCESS;
}
