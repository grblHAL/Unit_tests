#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    CHECK(N_AXIS == 6);
    parameter_words_t words = {.a = true, .b = true, .c = true, .f = true, .r = true};
    CHECK(gc_paramwords_to_axes(words).mask == 0);
    words.w = true;
    CHECK(gc_paramwords_to_axes(words).mask == 32);
    return EXIT_SUCCESS;
}
