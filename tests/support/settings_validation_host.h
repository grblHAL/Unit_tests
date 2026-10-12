#pragma once
#include "support/engine_host.h"
#include "settings.h"
/* Upstream exports this validator without declaring it in settings.h.
   Exercise metadata validation directly without changing the core source. */
status_code_t setting_validate_me(const setting_detail_t *setting, float value, char *svalue);
