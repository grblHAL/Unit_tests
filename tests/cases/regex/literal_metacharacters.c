#include "regex.h"
#include "check.h"

int main(void)
{
    CHECK(match("^a+b$", "a+b") == 1);
    CHECK(match("^a+b$", "aaab") == 0);
    CHECK(match("^a?b$", "a?b") == 1);
    return EXIT_SUCCESS;
}
