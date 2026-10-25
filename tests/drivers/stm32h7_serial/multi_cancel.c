#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_triplex_prepare();
    for (unsigned n = 0; n < 3; n++)
        stmh7_receive_port(n, 'A' + n);
    stmh7_port_stream[1]->cancel_read_buffer();
    stmh7_port_stream[2]->reset_read_buffer();
    CHECK(stmh7_port_stream[0]->read() == 'A' && stmh7_port_stream[0]->read() == SERIAL_NO_DATA);
    CHECK(stmh7_port_stream[1]->read() == ASCII_CAN &&
          stmh7_port_stream[1]->read() == SERIAL_NO_DATA);
    CHECK(stmh7_port_stream[2]->read() == SERIAL_NO_DATA);
    stmh7_receive_port(1, 'X');
    stmh7_receive_port(2, 'Y');
    CHECK(stmh7_port_stream[1]->read() == 'X' && stmh7_port_stream[2]->read() == 'Y');
    return 0;
}
