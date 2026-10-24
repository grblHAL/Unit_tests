#include "misc_host.h"
void feed_override_init(void);
void prepare_m220(void) { prepare_hooks(); feed_override_init(); }
