#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    CHECK(strcmp(btoa(3145728ULL), "3.00 MB") == 0);
    return EXIT_SUCCESS;
}
