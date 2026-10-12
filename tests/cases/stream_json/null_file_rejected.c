#include "support/engine_host.h"
#include "vfs.h"
#include "stream_json.h"
#include "check.h"

int main(void)
{
    CHECK(json_start(NULL, 4) == NULL);
    CHECK(!json_end(NULL));
    return EXIT_SUCCESS;
}
