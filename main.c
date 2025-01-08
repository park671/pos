#include "uart.h"

//use for test .bss
int x;
int y;
int z;
int a;
int b;
int c;

void main() {
    uart_printf("park hello world!\n\r");
}

void on_bss_fill() {
    uart_printf(".bss fill 8byte\n\r");
}
