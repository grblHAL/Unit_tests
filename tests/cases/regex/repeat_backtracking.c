#include "regex.h"
#include "check.h"

int main(void)
{
    CHECK(match("^a*ab$", "aaaab") == 1);
    CHECK(match("^.*abc$", "abcabc") == 1);
    CHECK(match("^.*abc$", "abcab") == 0);
    return EXIT_SUCCESS;
}
