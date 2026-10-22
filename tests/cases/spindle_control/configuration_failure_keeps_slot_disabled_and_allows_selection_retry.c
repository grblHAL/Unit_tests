#include "support/engine_host.h"
#include "spindle_control.h"
#include "check.h"

static void driver_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{ (void)spindle; (void)rpm; CHECK(!state.on); }
static spindle_state_t driver_state(spindle_ptrs_t *spindle)
{ (void)spindle; return (spindle_state_t){0}; }
static spindle_ptrs_t listed_spindle = {.type = SpindleType_Basic,
    .set_state = driver_output, .get_state = driver_state};

static bool configure_ok;
static unsigned configure_calls, selected_calls;
static bool configure_driver(spindle_ptrs_t *spindle)
{
    CHECK(spindle->type == SpindleType_Basic);
    configure_calls++;
    if(configure_ok)
        spindle->cap.direction = true;
    return configure_ok;
}
static void selected_driver(spindle_ptrs_t *spindle)
{
    CHECK(spindle->type == SpindleType_Basic && spindle->param != NULL);
    selected_calls++;
}
int main(void)
{
    engine_prepare();
    sys.cold_start = true;
    listed_spindle.config = configure_driver;
    grbl.on_spindle_selected = selected_driver;
    CHECK(spindle_register(&listed_spindle, "retry spindle") == 0);
    CHECK(spindle_get_default() == -2);
    CHECK(!spindle_get_caps(false).direction && !spindle_get_caps(true).direction);
    CHECK(!spindle_select(0));
    CHECK(configure_calls == 1 && selected_calls == 0);
    CHECK(!spindle_is_enabled(0) && spindle_get(0) == NULL);
    CHECK(spindle_get_default() == -2 && spindle_get_count() == 1);

    configure_ok = true;
    CHECK(spindle_select(0));
    CHECK(configure_calls == 2 && selected_calls == 1);
    CHECK(spindle_is_enabled(0) && spindle_get_default() == 0);
    CHECK(!spindle_get_caps(false).direction && spindle_get_caps(true).direction);
    CHECK(spindle_get(0)->cap.direction);
    CHECK(!listed_spindle.cap.direction);
    CHECK(spindle_get(0)->set_state == driver_output);
    CHECK(spindle_get(0)->get_state == driver_state);
    CHECK(spindle_select(0));
    CHECK(configure_calls == 2 && selected_calls == 1);
    return EXIT_SUCCESS;
}
