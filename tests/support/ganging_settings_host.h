#pragma once
#include "support/ganging_host.h"
static inline const setting_detail_t *ganged_resolution_definition(void)
{
    for(setting_details_t *details = settings_get_details(); details; details = details->next)
        for(unsigned i = 0; i < details->n_settings; i++)
            if(details->settings[i].id == Setting_AxisStepsPerMM + 3)
                return &details->settings[i];
    CHECK(false);
    return NULL;
}
