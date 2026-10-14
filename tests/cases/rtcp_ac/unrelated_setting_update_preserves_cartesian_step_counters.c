#include "support/rtcp_host.h"
static void rtcp_changed(settings_t *current,settings_changed_flags_t changed)
{ CHECK(current == &settings); (void)changed; }
int main(void)
{
    prepare_rtcp(); grbl.on_settings_changed = rtcp_changed; sys.driver_started = true;
    for(unsigned axis = 0; axis < N_AXIS; axis++) sys.position[axis] = 100 + axis;
    char value[] = "0.03";
    CHECK(settings_store_setting(Setting_JunctionDeviation,value) == Status_OK);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(sys.position[axis] == (int32_t)(100 + axis));
    return EXIT_SUCCESS;
}
