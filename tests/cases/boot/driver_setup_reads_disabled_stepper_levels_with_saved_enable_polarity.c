#include "support/boot_host.h"
static unsigned initial_enable_reads;
static axes_signals_t initial_enable_levels;
static void save_enable_polarity(void)
{
    char mask[] = "5";
    CHECK(settings_store_setting(Setting_InvertStepperEnable, mask) == Status_OK);
}
static void initialize_driver_outputs(settings_t *loaded)
{
    CHECK(loaded == &settings);
    CHECK(loaded->steppers.enable_invert.mask == 5);
    CHECK(loaded->steppers.energize.mask == 0 && loaded->steppers.idle_lock_time == 0);
    initial_enable_levels = st_get_enable_out();
    initial_enable_reads++;
}
int main(void)
{
    boot_during_init = save_enable_polarity;
    boot_during_setup = initialize_driver_outputs;
    boot_program = "$4\n";
    CHECK(grbl_enter() == 0);
    CHECK(initial_enable_reads == 1 && initial_enable_levels.mask == 5);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(strstr(engine_output, "$4=5" ASCII_EOL) != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(state_get() == STATE_IDLE && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
