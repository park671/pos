#include "uart.h"

#define UART0_DR   0x00
#define UART0_FR   0x18

#define UART0_FR_TXFF (1 << 5)
#define UART0_FR_RXFE (1 << 4)

volatile unsigned int *uart0_port = (unsigned int *) 0x09000000;

void uart0_write(unsigned int data) {
    while (*(uart0_port + (UART0_FR / 4)) & UART0_FR_TXFF);
    *(uart0_port + (UART0_DR / 4)) = data;
}

unsigned int uart0_read() {
    while (*(uart0_port + (UART0_FR / 4)) & UART0_FR_RXFE);
    return *(uart0_port + (UART0_DR / 4));
}

void uart_put_char(const char value) {
    uart0_write(value);
}

void uart_puts(const char *msg) {
    while (*msg != '\0') {
        uart_put_char(*msg);
        msg++;
    }
}
