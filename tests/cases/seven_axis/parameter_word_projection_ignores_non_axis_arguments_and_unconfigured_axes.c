#include "support/engine_host.h"
#include "check.h"
#if N_AXIS != 7
#error This case requires seven configured axes
#endif
int main(void)
{
    parameter_words_t words = {.f = true, .i = true, .j = true, .k = true,
        .p = true, .q = true, .r = true, .s = true, .t = true, .v = true, .w = true};
    CHECK(gc_paramwords_to_axes(words).mask == 0);
    words.u = true; CHECK(gc_paramwords_to_axes(words).mask == 64);
    return EXIT_SUCCESS;
}
