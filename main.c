#include "uart_printf.h"

//use for test .bss
int x;
int y;
int z;
int a;
int b;
int c;

void main() {
    uart_put_char('a');
    fail_uart_printf("park hello world!\n\r");
}

void on_bss_fill() {
    uart_put_char('b');
    fail_uart_printf(".bss fill %dbyte\n\r", 8);
}
