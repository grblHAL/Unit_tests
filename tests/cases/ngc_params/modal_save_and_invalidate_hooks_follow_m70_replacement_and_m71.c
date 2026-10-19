#include "support/program_end_host.h"
#include "ngc_params.h"
static unsigned save_calls, invalidate_calls;
static void *saved_context;
static void observe_modal_action(modal_state_action_t action, modal_groups_t commands,
                                 void *context)
{
    (void)commands;
    CHECK(context != NULL);
    if(action == ModalState_Save) {
        if(save_calls) CHECK(context == saved_context);
        saved_context = context;
        save_calls++;
    } else {
        CHECK(action == ModalState_Invalidate && context == saved_context);
        gc_modal_snapshot_t *snapshot = context;
        NEAR(snapshot->modal.feed_rate, 254);
        CHECK(snapshot->modal.units_imperial && snapshot->modal.distance_incremental);
        invalidate_calls++;
    }
}
int main(void)
{
    prepare_program_end(false);
    grbl.on_modal_state_action = observe_modal_action;
    CHECK(program_block("F120M70") == Status_OK);
    CHECK(save_calls == 1 && ngc_modal_state_get() == saved_context);
    CHECK(program_block("G20G91F10") == Status_OK);
    CHECK(program_block("M70") == Status_OK);
    CHECK(save_calls == 2 && invalidate_calls == 0);
    CHECK(program_block("M71") == Status_OK);
    CHECK(invalidate_calls == 1 && ngc_modal_state_get() == NULL);
    CHECK(program_block("M71") == Status_OK);
    CHECK(invalidate_calls == 1);
    return EXIT_SUCCESS;
}
