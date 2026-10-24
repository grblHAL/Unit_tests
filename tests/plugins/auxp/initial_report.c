#include "auxp_host.h"
int main(void)
{
    auxp_prepare(true);
    auxp_report(false);
    CHECK(strcmp(output, "|Dout:|previous") == 0);
    auxp_report(false);
    CHECK(strcmp(output, "|previous") == 0);
    auxp_report(true);
    CHECK(strcmp(output, "|Dout:|previous") == 0);
    CHECK(reports == 3);
    return 0;
}
