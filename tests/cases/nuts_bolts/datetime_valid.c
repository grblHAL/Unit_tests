#include <string.h>
#include <time.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    struct tm *dt = get_datetime("2024-02-29T23:59:59Z");
    CHECK(dt != NULL); CHECK(dt->tm_year == 124); CHECK(dt->tm_mon == 1);
    CHECK(dt->tm_mday == 29); CHECK(dt->tm_hour == 23); CHECK(dt->tm_min == 59); CHECK(dt->tm_sec == 59);
    return EXIT_SUCCESS;
}
