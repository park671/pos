//
// Created by Park Yu on 2025/1/8.
//

#include "uart_printf.h"
#include "stdarg.h"

void uart_print_char(const char ch) {
    uart_put_char(ch);
}

void uart_print_int(const long long dec) {
    if (dec == 0) {
        return;
    }
    uart_print_int(dec / 10);
    uart_put_char((char) (dec % 10 + '0'));
}

void uart_print_str(const char *ptr) {
    while (*ptr) {
        uart_put_char(*ptr);
        ptr++;
    }
}

//fixme this is a wrong but simple way to impl
void uart_print_float(const float value, int num) {
    int index = 0;
    int scale = 1;
    while (index < num) {
        scale *= 10;
        index++;
    }
    long long decimal_part = (long long) (value * scale);

    long long part1 = decimal_part / scale;
    long long part2 = decimal_part - (part1 * scale);

    uart_print_int(part1);
    uart_put_char('.');
    uart_print_int(part2);
}
//
//asm(".global uart_printf\n"
//    "uart_printf:\n"
//    "stp     x29, x30, [sp, #-272]!\n"
//    "mov     x29, sp\n"
//    "str     x0, [sp, #24]\n"
//    "str     x1, [sp, #216]\n"
//    "str     x2, [sp, #224]\n"
//    "str     x3, [sp, #232]\n"
//    "str     x4, [sp, #240]\n"
//    "str     x5, [sp, #248]\n"
//    "str     x6, [sp, #256]\n"
//    "str     x7, [sp, #264]\n"
//    "str     q0, [sp, #80]\n"
//    "mov     x0, #0x32\n"
//    "bl      uart_put_char\n"
//    "str     q1, [sp, #96]\n"
//    "str     q2, [sp, #112]\n"
//    "str     q3, [sp, #128]\n"
//    "str     q4, [sp, #144]\n"
//    "str     q5, [sp, #160]\n"
//    "str     q6, [sp, #176]\n"
//    "str     q7, [sp, #192]\n"
//    "mov     w0, #0x31\n"
//    "bl      uart_put_char\n"
//    "ret\n");

void fail_uart_printf(const char *format, ...) {
//    uart_put_char('1');
    va_list args;
    va_start(args, format);
//    uart_put_char('2');
    while (*format) {
//        uart_put_char('3');
        if (*format != '%') {
            uart_put_char(*format);
        } else {
            format++;
            switch (*format) {
                case 'c': {
                    char value = va_arg(args,
                    int);
                    uart_print_char(value);
                    break;
                }
                case 'd': {
                    uart_put_char('#');
                    int value = va_arg(args,
                    int);
                    uart_print_int(value);
                    break;
                }
                case 's': {
                    char *value = va_arg(args,
                    char *);
                    uart_print_str(value);
                    break;
                }
                default: {
                    uart_print_char('%');
                    uart_print_char(*format);
                }
            }
        }
        format++;
    }
//    uart_put_char('4');
    va_end(args);
}