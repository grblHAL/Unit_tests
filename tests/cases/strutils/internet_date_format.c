#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    struct tm dt = {.tm_year = 124, .tm_mon = 1, .tm_mday = 29, .tm_hour = 12, .tm_min = 34, .tm_sec = 56, .tm_wday = 4};
    CHECK(strcmp(strtointernetdt(&dt), "Thu, 29 Feb 2024 12:34:56 GMT") == 0);
    CHECK(strcmp(strtointernetdt(NULL), "Thu, 01 Jan 1970 00:00:00 GMT") == 0);
    return EXIT_SUCCESS;
}
