#include "stm7_serial_host.h"
int main(void)
{
    stm7_triplex_prepare();
    for (unsigned n = 0; n < 3; n++)
        stm7_receive_port(n, 'A' + n);
    stm7_port_stream[1]->cancel_read_buffer();
    stm7_port_stream[2]->reset_read_buffer();
    CHECK(stm7_port_stream[0]->read() == 'A' && stm7_port_stream[0]->read() == SERIAL_NO_DATA);
    CHECK(stm7_port_stream[1]->read() == ASCII_CAN &&
          stm7_port_stream[1]->read() == SERIAL_NO_DATA);
    CHECK(stm7_port_stream[2]->read() == SERIAL_NO_DATA);
    stm7_receive_port(1, 'X');
    stm7_receive_port(2, 'Y');
    CHECK(stm7_port_stream[1]->read() == 'X' && stm7_port_stream[2]->read() == 'Y');
    return 0;
}
