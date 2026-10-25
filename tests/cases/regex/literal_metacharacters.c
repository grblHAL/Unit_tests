#include "regex.h"
#include "check.h"

int main(void)
{
    CHECK(match("^a+b$", "a+b") == 1);
    CHECK(match("^a+b$", "aaab") == 0);
    CHECK(match("^a?b$", "a?b") == 1);
    CHECK(match("^$110=.*$", "$110=500.000") == 1);
    CHECK(match("^$110=.*$", "$111=500.000") == 0);
    CHECK(match("^$110=.*$", "prefix$110=500.000") == 0);
    return EXIT_SUCCESS;
}
