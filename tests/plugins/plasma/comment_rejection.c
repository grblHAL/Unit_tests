#include "plasma_host.h"
int main(void)
{
    plasma_prepare(3, true);
    plasma_load();
    char invalid[] = "o=1,nu=7,ph=3";
    CHECK(plasma_comment(invalid) == Status_GcodeValueWordMissing);
    CHECK(plasma_list() == Status_OK && !strstr(plasma_output, "nu:7"));
    char valid[] = "o=1,nu=7,ph=3,pd=0.5,ch=1,fr=900,th=1";
    CHECK(plasma_comment(valid) == Status_OK);
    CHECK(plasma_list() == Status_OK && strstr(plasma_output, "nu:7"));
    return 0;
}
