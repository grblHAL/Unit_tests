#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    const char *text = "Spindle Speed";
    CHECK(stristr(text, "SPINDLE") == text);
    CHECK(stristr(text, "speed") == text + 8);
    CHECK(stristr(text, "absent") == NULL);
    CHECK(stristr(text, "") == text);
    CHECK(stristr(text, NULL) == text);
    const char *restart = "abxabc";
    CHECK(stristr(restart, "ABC") == restart + 3);
    CHECK(stristr(text, "Speedometer") == NULL);
    const char *labels = "Spindle {rpx} {RPM}";
    CHECK(stristr(labels, "{rpm}") == labels + 14);
    CHECK(stristr(labels, "{rpx}") == labels + 8);
    CHECK(stristr(labels, "{rPm] ") == NULL);
    return EXIT_SUCCESS;
}
