#include "support/spindle_sync_parser_host.h"
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
    CHECK(sync_parser_block("G33Z1K1") == Status_OK);
    CHECK(axis_pulses[Z_AXIS] == 80 && sys.position[Z_AXIS] == 80);
    status_code_t status = sync_parser_block("G33.1Z2K1");
    fprintf(stderr, "Declined tapping: status=%u, parser Z=%g, physical steps=%ld\n",
            (unsigned)status, (double)gc_state.position[Z_AXIS], (long)physical_position[Z_AXIS]);
    CHECK(status == Status_GcodeUnsupportedCommand);
    NEAR(gc_state.position[Z_AXIS], 1);
    CHECK(physical_position[Z_AXIS] == 80 && sys.position[Z_AXIS] == 80);
    CHECK(axis_pulses[Z_AXIS] == 80 && plan_get_current_block() == NULL);
    CHECK(sync_parser_block("G33Z2K1") == Status_OK);
    CHECK(axis_pulses[Z_AXIS] == 160 && physical_position[Z_AXIS] == 160);
    CHECK(sys.position[Z_AXIS] == 160 && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
