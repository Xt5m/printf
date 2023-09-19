#include "main.h"

int _printf(const char *format, ...)
{
    if (!format)
        return -1;

    int i = 0, printed_chars = 0, flags, width, precision, size;
    char buffer[BUFF_SIZE];
    va_list list;

    va_start(list, format);

    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            flags = get_flags(format, &i);
            width = get_width(format, &i, list);
            precision = get_precision(format, &i, list);
            size = get_size(format, &i);
            printed_chars += handle_print(format, &i, list, buffer, flags, width, precision, size);
        }
        else
        {
            buffer[0] = format[i];
            buffer[1] = '\0';
            printed_chars += write(1, buffer, 1);
        }

        i++;
    }

    va_end(list);

    return printed_chars;
}
