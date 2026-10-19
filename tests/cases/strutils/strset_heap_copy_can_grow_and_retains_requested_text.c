#include <stdbool.h>
#include <stddef.h>
#include "strutils.h"
#include "check.h"
#include <stdlib.h>
#include <string.h>
int main(void)
{
    string_t text = {0};
    char *result = strset(&text, 32, "G21G90");
    CHECK(result != NULL && result == text.data);
    CHECK(text.data != NULL && text.len >= 32);
    CHECK(strcmp(text.data, "G21G90") == 0);
    result = strset(&text, 128, "G1X100Y100F500");
    CHECK(result != NULL && result == text.data);
    CHECK(text.len >= 128 && strcmp(text.data, "G1X100Y100F500") == 0);
    free(text.data);
    return EXIT_SUCCESS;
}
