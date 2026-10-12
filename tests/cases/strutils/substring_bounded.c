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
    CHECK(strnistr(text, "de", 2) == text + 3);
    return EXIT_SUCCESS;
}
