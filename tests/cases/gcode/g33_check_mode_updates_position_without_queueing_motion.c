#include "support/sync_parser_host.h"
#include "check.h"

static status_code_t decline_tapping(macro_id_t id, line_number_t line, parameter_words_t args, uint32_t repeats)
{
    CHECK(id == 331 && args.z && args.k && repeats == 1);
    (void)line;
    return Status_GcodeUnsupportedCommand;
}
int main(void)
{
    prepare_sync_parser();
    grbl.on_macro_execute = decline_tapping;
    CHECK(css_block("G33Z1K0.1") == Status_OK);
    NEAR(gc_state.position[Z_AXIS], 1.0f);
    NEAR(gc_state.distance_per_rev, 0.1f);
    CHECK(plan_get_current_block() == NULL);
    CHECK(!sys.override.control.feed_rates_disable);
    CHECK(!sys.override.control.spindle_rpm_disable);
    /* An unavailable tapping provider must leave check-mode position unchanged. */
    CHECK(css_block("G33.1Z2K0.2I2") == Status_GcodeUnsupportedCommand);
    NEAR(gc_state.position[Z_AXIS], 1.0f);
    NEAR(gc_state.distance_per_rev, 0.2f);
    CHECK(plan_get_current_block() == NULL);
    CHECK(!sys.override.control.feed_rates_disable);
    CHECK(!sys.override.control.spindle_rpm_disable);
    CHECK(css_block("G33Z3") == Status_OK);
    NEAR(gc_state.position[Z_AXIS], 3.0f);
    NEAR(gc_state.distance_per_rev, 0.2f);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
