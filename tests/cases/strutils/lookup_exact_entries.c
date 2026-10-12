#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    CHECK(strlookup("y", "x,y,z", ',') == 1);
    CHECK(strlookup("z", "x,y,z", ',') == 2);
    CHECK(strlookup("Y", "x,y,z", ',') == -1);
    CHECK(strlookup("xy", "x,y,z", ',') == -1);
    CHECK(strlookup("x", "", ',') == -1);
    return EXIT_SUCCESS;
}
