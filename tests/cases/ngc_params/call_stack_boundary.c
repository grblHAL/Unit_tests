#include "support/engine_host.h"
#include "ngc_params.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    int contexts[10]; CHECK(ngc_call_level() == 0); for(int i=0; i<10; i++) CHECK(ngc_call_push(&contexts[i])); CHECK(ngc_call_level() == 10); CHECK(!ngc_call_push(contexts)); for(int i=0; i<10; i++) { (void)ngc_call_pop(); CHECK(ngc_call_level() == 9-i); } CHECK(!ngc_call_pop()); CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
