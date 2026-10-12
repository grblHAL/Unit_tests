#include "regex.h"
#include "check.h"

int main(void)
{
    CHECK(match("abc", "xxabcxx") == 1);
    CHECK(match("abc", "ab") == 0);
    CHECK(match("abc", "ABC") == 0);
    return EXIT_SUCCESS;
}
