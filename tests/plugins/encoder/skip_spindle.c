#include "encoder_host.h"
int main(void)
{
 encoder_prepare(2, true); encoder_load();
 CHECK(encoder_handlers[0] == NULL); fprintf(stderr, "claimed encoders=%u\n", encoder_claims);
 CHECK(encoder_claims == 1 && encoder_handlers[1]); return 0;
}
