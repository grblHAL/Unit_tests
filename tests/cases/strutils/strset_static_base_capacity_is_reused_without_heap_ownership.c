#include <stdbool.h>
#include <stddef.h>
#include "strutils.h"
#include "check.h"
#include <stdlib.h>
#include <string.h>
int main(void)
{
    char filename[64] = "old_panel.nc";
    string_t base = {.data = filename, .len = sizeof(filename) - 1};
    string_t text = {.base = &base};
    CHECK(strset(&text, 32, "new_panel.nc") == filename);
    CHECK(text.data == filename && text.len == sizeof(filename) - 1);
    CHECK(strcmp(filename, "new_panel.nc") == 0);
    CHECK(strset(&text, 32, NULL) == filename && filename[0] == '\0');
    return EXIT_SUCCESS;
}
