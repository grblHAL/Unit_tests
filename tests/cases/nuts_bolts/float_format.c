#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    CHECK(strcmp(ftoa(1.25f, 2), "1.25") == 0);
    CHECK(strcmp(ftoa(-12.5f, 3), "-12.500") == 0);
    CHECK(strcmp(ftoa(0, 0), "0.") == 0);
    CHECK(strcmp(ftoa(1.999f, 2), "2.00") == 0);
    return EXIT_SUCCESS;
}
