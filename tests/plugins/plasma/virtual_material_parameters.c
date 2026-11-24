#include "plasma_host.h"
int main(void)
{
    plasma_prepare(3, true);
    plasma_load();
    char first[] = "o=0,ph=3,pd=0.5,ch=1,fr=900,kw=1.2,th=1";
    CHECK(plasma_comment(first) == Status_OK);
    NEAR(plasma_param("_hal[plasmac.cut-feed-rate]"), 900);
    NEAR(plasma_param("_hal[plasmac_run.kerf-width-f]"), 1.2f);
    char next[] = "o=0,ph=3,pd=0.5,ch=1,fr=1200,th=1";
    CHECK(plasma_comment(next) == Status_OK);
    NEAR(plasma_param("_hal[plasmac.cut-feed-rate]"), 1200);
    NEAR(plasma_param("_hal[plasmac_run.kerf-width-f]"), 0);
    return 0;
}
