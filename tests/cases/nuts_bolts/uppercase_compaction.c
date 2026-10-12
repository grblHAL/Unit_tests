#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    char input[32] = " g1 x2 y-3 ";
    CHECK(strcaps(input) == input); CHECK(strcmp(input, "G1X2Y-3") == 0);
    char empty[4] = "   "; CHECK(strcmp(strcaps(empty), "") == 0);
    return EXIT_SUCCESS;
}
