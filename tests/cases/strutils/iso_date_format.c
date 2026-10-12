#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    struct tm dt = {.tm_year = 124, .tm_mon = 1, .tm_mday = 29, .tm_hour = 12, .tm_min = 34, .tm_sec = 56};
    CHECK(strcmp(strtoisodt(&dt), "2024-02-29T12:34:56") == 0);
    CHECK(strcmp(strtoisodt(NULL), "") == 0);
    return EXIT_SUCCESS;
}
