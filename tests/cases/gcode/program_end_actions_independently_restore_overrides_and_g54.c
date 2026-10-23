#include "support/program_end_storage_host.h"
int main(void)
{
    prepare_program_end(false);
    CHECK(program_block("G10L2P1X3Y4") == Status_OK);
    CHECK(program_block("G10L2P2X8Y9") == Status_OK);
    unsigned completions = 0;
    for(unsigned actions = 0; actions < 4; actions++) {
        char value[] = {(char)('0' + actions), '\0'};
        CHECK(store_setting(Setting_EndProgramActions, value) == Status_OK);
        const setting_detail_t *detail = setting_get_details(Setting_EndProgramActions, NULL);
        CHECK(detail != NULL && strcmp(setting_get_value(detail, 0), value) == 0);
        for(unsigned m30 = 0; m30 < 2; m30++) {
            CHECK(program_block("G55") == Status_OK);
            plan_feed_override(125, 50);
            CHECK(program_block(m30 ? "M30" : "M2") == Status_OK);
            CHECK(program_complete_calls == ++completions);
            CHECK(program_completion == (m30 ? ProgramFlow_CompletedM30 : ProgramFlow_CompletedM2));
            CHECK(sys.override.feed_rate == ((actions & 1) ? 100 : 125));
            CHECK(sys.override.rapid_rate == ((actions & 1) ? 100 : 50));
            CHECK(gc_state.modal.g5x_offset.id == ((actions & 2) ? CoordinateSystem_G54 : CoordinateSystem_G55));
            NEAR(gc_state.modal.g5x_offset.data.coord.values[X_AXIS], (actions & 2) ? 3 : 8);
            NEAR(gc_state.modal.g5x_offset.data.coord.values[Y_AXIS], (actions & 2) ? 4 : 9);
        }
    }
    return EXIT_SUCCESS;
}
