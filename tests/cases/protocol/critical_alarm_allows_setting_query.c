#include "support/critical_alarm_host.h"
#include "check.h"

int main(void)
{
    run_critical_alarm_input("$100\n", 1);
    CHECK(lock_last_status == Status_OK);
    CHECK(strstr(engine_output, "$100=80.000") != NULL);
    return EXIT_SUCCESS;
}
