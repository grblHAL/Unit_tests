#include "regex.h"
#include "check.h"

int main(void)
{
    CHECK(match("", "") == 1);
    CHECK(match("", "anything") == 1);
    CHECK(match("^$", "") == 1);
    CHECK(match("^$", "x") == 0);
    return EXIT_SUCCESS;
}
