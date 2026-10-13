#pragma once
#include "support/settings_host.h"
/* Exported by the pinned core, without a declaration in settings.h. */
status_code_t setting_validate(setting_id_t id, float value, char *svalue);
status_code_t setting_validate_me(const setting_detail_t *setting, float value, char *svalue);
