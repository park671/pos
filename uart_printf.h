//
// Created by Park Yu on 2025/1/8.
//

#ifndef PUNIX_UART_PRINTF_H
#define PUNIX_UART_PRINTF_H

#include "uart.h"

void uart_printf(const char *format, ...);
void fail_uart_printf(const char *format, ...);

#endif //PUNIX_UART_PRINTF_H
