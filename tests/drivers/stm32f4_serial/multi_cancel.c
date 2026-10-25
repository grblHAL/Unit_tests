#include "stm_serial_host.h"
int main(void)
{
    stm_triplex_prepare();
    for (unsigned n = 0; n < 3; n++)
        stm_receive_port(n, 'A' + n);
    stm_port_stream[1]->cancel_read_buffer();
    stm_port_stream[2]->reset_read_buffer();
    CHECK(stm_port_stream[0]->read() == 'A' && stm_port_stream[0]->read() == SERIAL_NO_DATA);
    CHECK(stm_port_stream[1]->read() == ASCII_CAN && stm_port_stream[1]->read() == SERIAL_NO_DATA);
    CHECK(stm_port_stream[2]->read() == SERIAL_NO_DATA);
    stm_receive_port(1, 'X');
    stm_receive_port(2, 'Y');
    CHECK(stm_port_stream[1]->read() == 'X' && stm_port_stream[2]->read() == 'Y');
    return 0;
}
