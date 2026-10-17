#include "support/cutter_capture_host.h"
#include "probe.h"
static bool probe_input;
static unsigned probe_reads;
static bool read_probe(void *data)
{
    CHECK(data == &probe_input);
    probe_reads++;
    return probe_input;
}
int main(void)
{
    prepare_cutter_capture();
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_None, &probe_input, read_probe));
    CHECK(cutter_block("G41.1D6") == Status_OK);
    unsigned reads_before = probe_reads;
    CHECK(cutter_block("G38.2Z-5F100") == Status_CutterCompConflict);
    CHECK(probe_reads == reads_before);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Left);
    NEAR(gc_state.position[Z_AXIS], 0);
    CHECK(cutter_enable_calls == 1 && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
