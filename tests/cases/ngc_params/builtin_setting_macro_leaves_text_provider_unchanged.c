#include "support/builtin_macro_host.h"
#include "support/plugin_text_settings_host.h"

int main(void)
{
    prepare_plugin_text_settings();
    /* P1 supplies numeric settings; a label must not be converted from S. */
    CHECK(builtin_macro_block("G65P1Q1001S123") == Status_OK);
    NEAR(builtin_macro_result("_value_returned"), 0);
    CHECK(strcmp(plugin_label, "router") == 0);
    CHECK(plugin_text_saves == 0 && plugin_text_changes == 0);
    CHECK(strcmp(plugin_password, "sample-key") == 0);
    CHECK(builtin_macro_block("G65P1Q13S1") == Status_OK);
    NEAR(builtin_macro_result("_value_returned"), 1);
    NEAR(builtin_macro_result("_value"), 1);
    CHECK(settings.flags.report_inches);
    CHECK(strcmp(plugin_label, "router") == 0);
    CHECK(plugin_text_saves == 0 && plugin_text_changes == 0);
    return EXIT_SUCCESS;
}
