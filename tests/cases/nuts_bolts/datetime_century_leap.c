#include <time.h>
#include "nuts_bolts.h"
#include "check.h"
int main(void)
{
    CHECK(get_datetime("2000-02-29T00:00:00Z") != NULL);
    return EXIT_SUCCESS;
}
