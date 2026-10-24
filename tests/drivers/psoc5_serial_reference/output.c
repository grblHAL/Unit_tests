#include "psoc_host.h"
int main(void)
{
    psoc_start();
    psoc_stream->write("ok\n");
    CHECK(psoc_stream->write_char('!'));
    const char binary[] = {0, (char)0x80, (char)0xff};
    psoc_stream->write_n(binary, sizeof(binary));
    CHECK(sent_count == 7 && memcmp(sent, "ok\n!", 4) == 0 && sent[4] == 0 && sent[5] == 0x80 &&
          sent[6] == 0xff);
    return 0;
}
