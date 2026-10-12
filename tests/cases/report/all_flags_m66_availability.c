#include "support/engine_host.h"
#include "report.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    sys.var5399 = -2;
    CHECK(!report_get_rt_flags_all().m66result);
    sys.var5399 = 0;
    CHECK(report_get_rt_flags_all().m66result);
    return EXIT_SUCCESS;
}
