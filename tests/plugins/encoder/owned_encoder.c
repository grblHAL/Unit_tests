#include "encoder_host.h"
static unsigned other_events;
static void other_owner(encoder_t *encoder, encoder_event_t *event, void *context)
{ CHECK(encoder == &encoder_devices[0] && context == &other_events); other_events++; event->value = 0; }
int main(void)
{
 encoder_prepare(1, false);
 CHECK(encoder_devices[0].claim(&encoder_devices[0], other_owner, &other_events)); encoder_load();
 CHECK(encoder_claims == 1 && encoder_handlers[0] == other_owner && encoder_configures == 0 && encoder_resets == 0);
 encoder_emit(0, 4, 100, (encoder_event_t){.position_changed = On}); CHECK(other_events == 1 && encoder_command_count == 0); return 0;
}
