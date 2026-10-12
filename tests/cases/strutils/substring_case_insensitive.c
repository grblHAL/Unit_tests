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
    return EXIT_SUCCESS;
}
