/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:03:16 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/18 17:24:55 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	vl_print(va_list vl, const char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(vl, int)));
	if (c == 's')
		return (ft_putstr(va_arg(vl, const char *)));
	if (c == 'p')
	{
		ft_putchar('0');
		ft_putchar('x');
		return (ft_putnbr_hex(va_arg(vl, unsigned long)) + 2);
	}
	if (c == 'd')
		return (ft_putnbr(va_arg(vl, int)));
	if (c == 'i')
		return (ft_putnbr(va_arg(vl, int)));
	if (c == 'u')
		return (ft_unsigned_putnbr(va_arg(vl, unsigned int)));
	if (c == 'x')
		return (ft_putnbr_hex(va_arg(vl, unsigned int)));
	if (c == 'X')
		return (ft_putnbr_upper_hex(va_arg(vl, unsigned int)));
	if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	vl;
	int		idx;
	int		count;

	idx = 0;
	count = 0;
	va_start(vl, fmt);
	while (fmt[idx])
	{
		if (fmt[idx] != '%')
			count += ft_putchar(fmt[idx]);
		else if (fmt[idx] == '%')
			count += vl_print(vl, fmt[idx++ + 1]);
		idx++;
	}
	return (count);
}
