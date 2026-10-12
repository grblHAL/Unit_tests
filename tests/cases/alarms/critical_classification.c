#include "core_handlers.h"
#include "check.h"

int main(void)
{
    CHECK(alarm_is_critical(Alarm_HardLimit)); CHECK(alarm_is_critical(Alarm_SoftLimit));
    CHECK(alarm_is_critical(Alarm_EStop)); CHECK(alarm_is_critical(Alarm_MotorFault));
    CHECK(alarm_is_critical(Alarm_ExpanderException));
    CHECK(!alarm_is_critical(Alarm_HomingRequired)); CHECK(!alarm_is_critical(Alarm_ProbeFailContact));
    return EXIT_SUCCESS;
}
