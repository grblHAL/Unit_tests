#include <stdbool.h>
#include <stddef.h>
#include "strutils.h"
#include "check.h"
#include <stdlib.h>
#include <string.h>
int main(void)
{
    string_t text = {0};
    CHECK(strset(&text, 0, "") != NULL);
    CHECK(text.len == 0 && text.data[0] == '\0');
    char *grown = strset(&text, 1, "X");
    CHECK(grown == text.data);
    CHECK(strcmp(text.data, "X") == 0);
    free(text.data);
    return EXIT_SUCCESS;
}
