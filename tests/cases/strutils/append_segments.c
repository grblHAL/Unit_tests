#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    char buffer[32] = "old";
    CHECK(strappend(buffer, 3, "G1", " X", "10") == buffer);
    CHECK(strcmp(buffer, "G1 X10") == 0);
    CHECK(strcmp(strappend(buffer, 2, "", "abc"), "abc") == 0);
    return EXIT_SUCCESS;
}
