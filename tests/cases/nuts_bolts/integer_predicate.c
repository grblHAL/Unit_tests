#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    CHECK(isintf(0)); CHECK(isintf(-2)); CHECK(isintf(12.0005f));
    CHECK(!isintf(12.25f)); CHECK(!isintf(NAN)); CHECK(!isintf(INFINITY));
    return EXIT_SUCCESS;
}
