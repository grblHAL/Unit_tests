#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    CHECK(strcmp(btoa(2048ULL), "2.00 KB") == 0);
    return EXIT_SUCCESS;
}
