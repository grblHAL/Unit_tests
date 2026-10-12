#include "regex.h"
#include "check.h"

int main(void)
{
    CHECK(match("^ab*c$", "abbbbc") == 1);
    CHECK(match("^ab*c$", "abdc") == 0);
    CHECK(match("^a*$", "aaaa") == 1);
    return EXIT_SUCCESS;
}
