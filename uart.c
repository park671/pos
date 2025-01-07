#include "uart.h"

volatile unsigned int *uart0_port = (unsigned int *) 0x09000000;

void uart_printf(const char *msg) {
    while (*msg != '\0')
    {
        *uart0_port = (unsigned int)(*msg);
        msg++;
    }
}
