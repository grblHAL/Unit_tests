#include <stdbool.h>
#include <string.h>
#include "strutils.h"
#include "check.h"

int main(void)
{
    const char *text = "aaAb";
    CHECK(stristr(text, "aab") == text + 1);
    CHECK(stristr("abc", "abcd") == NULL);
    CHECK(stristr("", "a") == NULL);
    return EXIT_SUCCESS;
}
