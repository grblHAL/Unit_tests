#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    char input[32] = " g1 x2 y-3 ";
    CHECK(strcaps(input) == input); CHECK(strcmp(input, "G1X2Y-3") == 0);
    char empty[4] = "   "; CHECK(strcmp(strcaps(empty), "") == 0);
    char compact[] = "g1x2y-3";
    CHECK(strcaps(compact) == compact);
    CHECK(strcmp(compact, "G1X2Y-3") == 0);
    char no_text[] = "";
    CHECK(strcaps(no_text) == no_text && no_text[0] == '\0');
    char startup[] = " g1 x2 | g1 x3 ";
    CHECK(strcaps(startup) == startup);
    CHECK(strcmp(startup, "G1X2|G1X3") == 0);
    return EXIT_SUCCESS;
}
