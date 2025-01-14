#include "uart.h"
#include "stdarg.h"

volatile unsigned int *uart0_port = (unsigned int *) 0x09000000;
static const unsigned int FR_OFFSET = 0x018;
static const unsigned int FR_BUSY = (1 << 3);

void wait_for_complete() {
    while ((*(uart0_port + FR_OFFSET) * FR_BUSY) != 0) {}
}

void simple_put_char(const char data) {
    wait_for_complete();
    *uart0_port = (unsigned int) (data);
    wait_for_complete();
}

void simple_puts(const char *msg) {
    while (*msg != '\0') {
        simple_put_char(*msg);
        msg++;
    }
}

char print_buffer[256];

int buffer_print_int(const long long dec) {
    if (dec == 0) {
        return 0;
    }
    int index = buffer_print_int(dec / 10);
    print_buffer[index] = ((char) (dec % 10 + '0'));
    return index + 1;
}

void simple_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int i = 0;
    char format_next_type = 0;
    for (i = 0; format[i] != '\0'; i++) {
        if (format_next_type) {
            switch (format[i]) {
                case '%': {
                    simple_put_char('%');
                    break;
                }
                case 'd': {
                    int value = va_arg(args, int);
                    int length = buffer_print_int(value);
                    print_buffer[length] = '\0';
                    simple_puts(print_buffer);
                    break;
                }
            }
            format_next_type = 0;
            continue;
        }
        if (format[i] == '%') {
            format_next_type = 1;
            continue;
        }
        simple_put_char(format[i]);
    }
    va_end(args);
}
