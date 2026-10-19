#include <stdbool.h>
#include <stddef.h>
#include "strutils.h"
#include "check.h"
#include <stdlib.h>
#include <string.h>
int main(void)
{
    char filename[64] = "panel.nc";
    char longer[128];
    memset(longer, 'a', 100);
    strcpy(longer + 100, ".macro");
    string_t base = {.data = filename, .len = sizeof(filename) - 1};
    string_t text = {.base = &base};
    CHECK(strset(&text, strlen(longer), longer) != NULL);
    CHECK(text.data != filename && text.len >= strlen(longer));
    CHECK(strcmp(text.data, longer) == 0);
    CHECK(strcmp(filename, "panel.nc") == 0);
    free(text.data);
    return EXIT_SUCCESS;
}
