#include "support/boot_host.h"
#include "ngc_params.h"

static unsigned fallback_calls;
static status_code_t driver_macro(macro_id_t id, line_number_t line, parameter_words_t words, uint32_t repeats)
{
    CHECK(id == 100 && line == 42 && words.x && repeats == 1);
    CHECK(ngc_call_level() == 1);
    float value;
    CHECK(ngc_param_get(24, &value)); NEAR(value, 12);
    fallback_calls++;
    return Status_OK;
}
static void register_driver_macro(void) { grbl.on_macro_execute = driver_macro; }

int main(void)
{
    boot_during_init = register_driver_macro;
    boot_program = "(operation setup)\n#24=99\nN42G65P100X12\nG65P3I100Q9\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(fallback_calls == 1 && ngc_call_level() == 0);
    CHECK(grbl.on_macro_execute != driver_macro);
    float value;
    CHECK(ngc_param_get(24, &value)); NEAR(value, 99);
    CHECK(ngc_param_get(100, &value)); NEAR(value, 9);
    CHECK(strstr(engine_output, "error:") == NULL && strstr(engine_output, "[GC:") != NULL);
    CHECK(strstr(engine_output, "operation setup") == NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
