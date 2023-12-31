#include "main.h"
/**
 * handle_print - to print an argument based on its type
 * @fmt: to format string in which to print the arguments.
 * @list: the list of arguments to be printed.
 * @ind: the ind.
 * @buffer: the buffer array to handle print.
 * @flags: to calculate active flags
 * @width: to get width.
 * @precision: to precision specification
 * @size: the size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));
	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
					--(*ind);
			if (fmt[*ind] == ' ')
					--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
