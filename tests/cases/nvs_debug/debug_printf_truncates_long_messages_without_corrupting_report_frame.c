#include "support/nvs_debug_host.h"
#include "stream.h"
int main(void)
{
    prepare_nvs_debug(); char text[161]; memset(text, 'x', 160); text[160] = 0;
    debug_printf("%s", text);
    CHECK(strncmp(engine_output, "[MSG:Debug: ", 12) == 0);
    CHECK(strlen(engine_output) < 160 && strlen(engine_output) > 12);
    CHECK(strcmp(engine_output + strlen(engine_output) - strlen("]" ASCII_EOL), "]" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
