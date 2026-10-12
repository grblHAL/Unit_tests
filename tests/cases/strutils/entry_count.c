#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    CHECK(strnumentries(NULL, ',') == 0);
    CHECK(strnumentries("", ',') == 0);
    CHECK(strnumentries("a", ',') == 1);
    CHECK(strnumentries(",a,,", ',') == 4);
    return EXIT_SUCCESS;
}
