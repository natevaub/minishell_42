/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:03:45 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/17 23:53:42 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr(int num)
{
	int	num_count;
	int	count;

	num_count = num;
	count = count_size(num_count);
	if (num == -2147483648)
		write(1, "-2147483648", 11);
	else if (num >= 0 && num < 10)
		ft_putchar(num + 48);
	else if (num < 0)
	{
		ft_putchar('-');
		ft_putnbr(num * (-1));
	}
	else
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	return (count);
}

unsigned int	ft_unsigned_putnbr(unsigned int num)
{
	unsigned int	num_count;
	unsigned int	count;

	num_count = num;
	count = count_unsigned_size(num_count);
	if (num < 10)
		ft_putchar(num + 48);
	else
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	return (count);
}
