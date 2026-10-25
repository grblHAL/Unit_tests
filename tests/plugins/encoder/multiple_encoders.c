#include "encoder_host.h"
int main(void)
{
 encoder_prepare(2, false); encoder_load(); CHECK(encoders_get_count() == 2);
 fprintf(stderr, "claimed encoders=%u\n", encoder_claims); CHECK(encoder_claims == 2 && encoder_handlers[0] && encoder_handlers[1]); return 0;
}
