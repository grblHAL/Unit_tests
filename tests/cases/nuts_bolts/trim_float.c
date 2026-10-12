#include <string.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    char a[] = "-12.34000", b[] = "0.000", c[] = "1000", d[] = "12.001";
    CHECK(trim_float(a) == a); CHECK(strcmp(a, "-12.34") == 0);
    CHECK(strcmp(trim_float(b), "0") == 0);
    CHECK(strcmp(trim_float(c), "1000") == 0);
    CHECK(strcmp(trim_float(d), "12.001") == 0);
    return EXIT_SUCCESS;
}
