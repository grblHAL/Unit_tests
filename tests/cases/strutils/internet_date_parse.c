#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    char text[] = "Thu, 29 Feb 2024 12:34:56 GMT"; struct tm dt = {0};
    CHECK(strtotime(text, &dt)); CHECK(dt.tm_year == 124); CHECK(dt.tm_mon == 1);
    CHECK(dt.tm_mday == 29); CHECK(dt.tm_hour == 12); CHECK(dt.tm_min == 34); CHECK(dt.tm_sec == 56);
    return EXIT_SUCCESS;
}
