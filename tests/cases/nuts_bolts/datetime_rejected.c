#include <string.h>
#include <time.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    const char *invalid[] = {"2023-02-29T00:00:00Z", "2024-04-31T00:00:00Z", "2024-13-01T00:00:00Z", "2024-01-01T24:00:00Z", "1969-01-01T00:00:00Z", "2100-01-01T00:00:00Z",
        "2024-00-01T00:00:00Z", "2024-01-00T00:00:00Z",
        "2024-01-01T00:60:00Z", "2024-01-01T00:00:60Z", "bad"};
    for(unsigned n = 0; n < sizeof(invalid)/sizeof(invalid[0]); n++) CHECK(get_datetime(invalid[n]) == NULL);
    struct tm *valid = get_datetime("2024-01-01T00:00:00Z");
    CHECK(valid != NULL && valid->tm_year == 124 && valid->tm_mon == 0 && valid->tm_mday == 1);
    CHECK(valid->tm_hour == 0 && valid->tm_min == 0 && valid->tm_sec == 0);
    return EXIT_SUCCESS;
}
