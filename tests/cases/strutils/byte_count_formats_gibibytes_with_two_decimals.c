#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    CHECK(strcmp(btoa(4294967296ULL), "4.00 GB") == 0);
    return EXIT_SUCCESS;
}
