#include "uart.h"

//use for test .bss
int x;
int y;
int z;
int a;
int b;
int c;

void main() {
    simple_puts("[+]main() start\n\r\0");
    simple_printf("park hello world!\n\r\0");
    simple_printf("simple test %d\n\r\0", 8);
    simple_puts("[+]main() finish\n\r\0");
}

void on_bss_fill() {
    simple_puts("on_bss_fill()\n\r\0");
}
