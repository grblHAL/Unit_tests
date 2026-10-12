#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    char buffer[32];
    CHECK(strgetentry(buffer, "x,y,z", 1, ',') == buffer); CHECK(strcmp(buffer, "y") == 0);
    CHECK(strcmp(strgetentry(buffer, "x,y,z", 2, ','), "z") == 0);
    CHECK(strcmp(strgetentry(buffer, "single", 0, ','), "single") == 0);
    CHECK(strcmp(strgetentry(buffer, "x,,z", 1, ','), "") == 0);
    return EXIT_SUCCESS;
}
