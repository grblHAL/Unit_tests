#include <string.h>
#include <time.h>
#include "nuts_bolts.h"
#include "check.h"

int main(void)
{
    const char *invalid[] = {"2023-02-29T00:00:00Z", "2024-04-31T00:00:00Z", "2024-13-01T00:00:00Z", "2024-01-01T24:00:00Z", "1969-01-01T00:00:00Z", "bad"};
    for(unsigned n = 0; n < sizeof(invalid)/sizeof(invalid[0]); n++) CHECK(get_datetime(invalid[n]) == NULL);
    return EXIT_SUCCESS;
}
