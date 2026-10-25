#include "support/multi_spindle_host.h"

int main(void)
{
    engine_prepare();
    sys.cold_start = true;
    for(unsigned i = 0; i < 2; i++)
        registered_spindles[i] = (spindle_ptrs_t){
            .type = SpindleType_Basic, .ref_id = (uint8_t)(10 * (i + 1)),
            .rpm_min = 1000, .rpm_max = 12000,
            .cap = {.direction = true, .rpm_range_locked = true},
            .config = spindle_configure, .set_state = spindle_output,
            .get_state = spindle_input
        };
    CHECK(spindle_register(&registered_spindles[0], "primary") == 0);
    CHECK(spindle_select(0));
    char oversized_name[101];
    memset(oversized_name, 'X', sizeof(oversized_name) - 1);
    oversized_name[sizeof(oversized_name) - 1] = 0;
    CHECK(spindle_register(&registered_spindles[1], oversized_name) == -1);
    CHECK(spindle_get_count() == 1);
    CHECK(strcmp(spindle_get_name(0), "primary") == 0);
    CHECK(spindle_get_name(1) == NULL);
    CHECK(spindle_register(&registered_spindles[1], "secondary") == 1);
    CHECK(spindle_get_count() == 2);
    CHECK(strcmp(spindle_get_name(1), "secondary") == 0);
    const setting_detail_t *selector = setting_get_details(Setting_SpindleType, NULL);
    CHECK(selector != NULL);
    CHECK(strcmp(selector->format, "primary,secondary") == 0);
    CHECK(spindle_select(1));
    spindle_ptrs_t *selected = spindle_get(0);
    CHECK(selected != NULL && selected->id == 1);
    CHECK(spindle_config_calls[0] == 1 && spindle_config_calls[1] == 1);
    return EXIT_SUCCESS;
}
