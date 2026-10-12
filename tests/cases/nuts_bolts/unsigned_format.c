#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    CHECK(strcmp(uitoa(0), "0") == 0);
    CHECK(strcmp(uitoa(4294967295U), "4294967295") == 0);
    CHECK(strcmp(uitoa(1000000000U), "1000000000") == 0);
    return EXIT_SUCCESS;
}
