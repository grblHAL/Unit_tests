#include "event_host.h"
static unsigned visits, stop_after;
static bool visit(const setting_detail_t *setting, uint_fast16_t offset, void *data)
{
    CHECK(data == &visits && offset == visits);
    CHECK(setting == event_details->settings);
    visits++;
    return visits != stop_after;
}
int main(void)
{
    load_events();
    const setting_detail_t *setting = event_details->settings;
    CHECK(event_details->iterator(setting, visit, &visits) && visits == 4);
    visits = 0;
    stop_after = 2;
    CHECK(!event_details->iterator(setting, visit, &visits) && visits == 2);
    CHECK(setting->is_available(setting, 3) && !setting->is_available(setting, 4));
    CHECK(event_details->normalize(Setting_ActionBase + 1) == Setting_ActionBase);
    CHECK(event_details->normalize(Setting_Action9) == Setting_ActionBase);
    CHECK(event_details->normalize(Setting_ActionPortBase + 1) == Setting_ActionPortBase);
    CHECK(event_details->normalize(Setting_ActionPort9) == Setting_ActionPortBase);
    CHECK(event_details->normalize(Setting_FanPort0) == 0);
    CHECK(writes == 0 && saves == 1);
    return 0;
}
