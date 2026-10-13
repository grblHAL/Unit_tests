#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    CHECK(strcmp(btoa(512ULL), "512 B") == 0);
    return EXIT_SUCCESS;
}
