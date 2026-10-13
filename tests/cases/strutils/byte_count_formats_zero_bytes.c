#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    CHECK(strcmp(btoa(0ULL), "0 B") == 0);
    return EXIT_SUCCESS;
}
