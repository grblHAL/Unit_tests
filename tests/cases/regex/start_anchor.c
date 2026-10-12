#include "regex.h"
#include "check.h"

int main(void)
{
    CHECK(match("^abc", "abcdef") == 1);
    CHECK(match("^abc", "xabc") == 0);
    CHECK(match("^", "") == 1);
    return EXIT_SUCCESS;
}
