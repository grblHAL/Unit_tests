#include "support/engine_host.h"
#include "check.h"
#if N_AXIS != 7
#error This case requires seven configured axes
#endif
int main(void)
{
    parameter_words_t words = {.x = true, .y = true, .z = true, .a = true,
        .b = true, .c = true, .u = true};
    CHECK(gc_paramwords_to_axes(words).mask == 127);
    return EXIT_SUCCESS;
}
