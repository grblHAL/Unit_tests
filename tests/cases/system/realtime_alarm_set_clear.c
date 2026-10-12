#include "support/engine_host.h"
#include "report.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    system_set_exec_alarm(Alarm_HardLimit);
    CHECK(sys.rt_exec_alarm == Alarm_HardLimit);
    system_clear_exec_alarm();
    CHECK(sys.rt_exec_alarm == 0);
    return EXIT_SUCCESS;
}
