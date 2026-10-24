#include "plasma_host.h"
int main(void)
{
    plasma_prepare(3, true);
    plasma_load();
    char add[] = "o=1,nu=7,na=Steel,ph=3,pd=0.5,ch=1,fr=900,th=1";
    CHECK(plasma_comment(add) == Status_OK);
    CHECK(plasma_list() == Status_OK && strstr(plasma_output, "nu:7"));
    char normal[] = "ordinary job comment";
    CHECK(plasma_comment(normal) == Status_Unhandled && plasma_prior_comments == 1);
    return 0;
}
