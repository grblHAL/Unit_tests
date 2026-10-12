#include "regex.h"
#include "check.h"

int main(void)
{
    CHECK(match("^ab*c$", "ac") == 1);
    CHECK(match("^a*$", "") == 1);
    CHECK(match("^ab*c$", "abb") == 0);
    return EXIT_SUCCESS;
}
