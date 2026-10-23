#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    const char *text = "abcdef";
    CHECK(strnistr(text, "ABCX", 3) == text);
    CHECK(strnistr(text, "ABCX", 4) == NULL);
    CHECK(strnistr(text, "xyz", 0) == text);
    CHECK(strnistr(text, "", 3) == text);
    CHECK(strnistr(text, NULL, 3) == text);
    CHECK(strnistr("", "a", 1) == NULL);
    CHECK(strnistr(text, "de", 2) == text + 3);
    const char *overlap = "aaab";
    CHECK(strnistr(overlap, "AAB", 3) == overlap + 1);
    CHECK(strnistr(overlap, "AAX", 3) == NULL);
    CHECK(strnistr(text, "DEFG", 4) == NULL);
    CHECK(strnistr(text, "def", 8) == text + 3);
    const char *restart = "abxabc";
    CHECK(strnistr(restart, "ABC", 3) == restart + 3);
    const char *labels = "Spindle {rpx} {RPM}";
    CHECK(strnistr(labels, "{rpm}", 5) == labels + 14);
    CHECK(strnistr(labels, "{RPM} suffix", 5) == labels + 14);
    CHECK(strnistr(labels, "{rPm]", 5) == NULL);
    return EXIT_SUCCESS;
}
