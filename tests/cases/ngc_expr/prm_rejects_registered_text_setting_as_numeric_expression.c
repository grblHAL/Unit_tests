#include "support/engine_host.h"
#include "ngc_expr.h"
#include "check.h"
static char machine_name[] = "Router";
static const setting_detail_t text_setting = {.id = (setting_id_t)1001,
    .name = "Machine name", .datatype = Format_String, .type = Setting_NonCore,
    .value = machine_name};
static void persist(void) {}
static setting_details_t details = {.n_settings = 1, .settings = &text_setting,
    .load = persist, .restore = persist, .save = persist};
int main(void)
{
    engine_parser_prepare();
    CHECK(settings_register(&details));
    char text[] = "[PRM[1001]]";
    uint_fast8_t pos = 0; float value = 0;
    CHECK(ngc_eval_expression(text, &pos, &value) == Status_ExpressionArgumentOutOfRange);
    CHECK(strcmp(machine_name, "Router") == 0);
    return EXIT_SUCCESS;
}
