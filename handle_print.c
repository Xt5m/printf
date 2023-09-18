#include "main.h"

int print_char_precision(va_list list, char buffer[], int flags, int width, int precision, int size) {
    char c = va_arg(list, int); // Note: char is promoted to int in varargs

    // Handle precision (for characters, precision is not applicable)
    if (precision >= 0) {
        // Precision is not applicable for characters
        // You can choose to ignore it or handle it differently if needed
    }

    // Print the character
    buffer[0] = c;
    buffer[1] = '\0';

    // Now, you can handle flags, width, and print the formatted character
    // (apply justification, width, and other formatting as needed)

    return 1; // Return the number of characters printed
}

int print_string_precision(va_list list, char buffer[], int flags, int width, int precision, int size) {
    char *str = va_arg(list, char*);

    // Handle precision
    if (precision >= 0) {
        int len = snprintf(NULL, 0, "%.*s", precision, str);
        snprintf(buffer, len + 1, "%.*s", precision, str);
    } else {
        snprintf(buffer, strlen(str) + 1, "%s", str);
    }

    // Now, you can handle flags, width, and print the formatted string
    // (apply justification, width, and other formatting as needed)

    return strlen(buffer); // Return the number of characters printed
}

int print_int_precision(va_list list, char buffer[], int flags, int width, int precision, int size) {
    int num = va_arg(list, int);

    // Handle precision
    if (precision >= 0) {
        snprintf(buffer, precision + 1, "%0*d", precision, num);
    } else {
        snprintf(buffer, sizeof(buffer), "%d", num);
    }

    // Now, you can handle flags, width, and print the formatted integer
    // (apply justification, width, and other formatting as needed)

    return strlen(buffer); // Return the number of characters printed
}

int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
    int flags, int width, int precision, int size) {
    int i, unknow_len = 0, printed_chars = -1;
    fmt_t fmt_types[] = {
        {'c', print_char_precision}, {'s', print_string_precision}, {'%', print_percent},
        {'i', print_int_precision}, {'d', print_int_precision}, {'b', print_binary},
        {'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
        {'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
        {'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
    };

    for (i = 0; fmt_types[i].fmt != '\0'; i++) {
        if (fmt[*ind] == fmt_types[i].fmt) {
            return fmt_types[i].fn(list, buffer, flags, width, precision, size);
        }
    }

    if (fmt_types[i].fmt == '\0') {
        if (fmt[*ind] == '\0') {
            return (-1);
        }
        unknow_len += write(1, "%%", 1);
        if (fmt[*ind - 1] == ' ') {
            unknow_len += write(1, " ", 1);
        } else if (width) {
            --(*ind);
            while (fmt[*ind] != ' ' && fmt[*ind] != '%') {
                --(*ind);
            }
            if (fmt[*ind] == ' ') {
                --(*ind);
            }
            return (1);
        }
        unknow_len += write(1, &fmt[*ind], 1);
        return (unknow_len);
    }
    return (printed_chars);
}
