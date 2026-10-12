#include "regex.h"
#include "check.h"

int main(void)
{
    CHECK(match("abc$", "xxabc") == 1);
    CHECK(match("abc$", "abcx") == 0);
    CHECK(match("$", "") == 1);
    return EXIT_SUCCESS;
}
