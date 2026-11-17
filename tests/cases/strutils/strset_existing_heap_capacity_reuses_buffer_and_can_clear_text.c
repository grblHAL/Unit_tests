#include <stdbool.h>
#include <stddef.h>
#include "strutils.h"
#include "check.h"
#include <stdlib.h>
#include <string.h>
int main(void)
{
    string_t text = {0};
    CHECK(HOST_STRSET(&text, 128, "fixture_panel.nc") != NULL);
    char *original = text.data;
    CHECK(HOST_STRSET(&text, 32, "next_panel.nc") == original);
    CHECK(strcmp(text.data, "next_panel.nc") == 0 && text.len >= 128);
    CHECK(HOST_STRSET(&text, 32, NULL) == original);
    CHECK(text.data[0] == '\0');
    free(text.data);
    return EXIT_SUCCESS;
}
