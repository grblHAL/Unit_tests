#include "support/builtin_macro_host.h"
#include "check.h"
static unsigned selection_calls;
static probe_id_t selected_probe;
static bool capture_selected_probe(probe_id_t id) { selection_calls++; selected_probe = id; return true; }

int main(void)
{
    prepare_settings_store();
    hal.probe.select = capture_selected_probe;
    CHECK(builtin_macro_block("G65P5Q1") == Status_OK);
    CHECK(selection_calls == 1);
    CHECK(selected_probe == Probe_Toolsetter);
    return EXIT_SUCCESS;
}
