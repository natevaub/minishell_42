/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:40:59 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/18 16:50:48 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_nbr_upper_hex(unsigned long num)
{
	if (num < 10)
		ft_putchar(num + 48);
	else if (num >= 10 && num < 16)
		ft_putchar(num + 'A' - 10);
	else
	{
		ft_nbr_upper_hex(num / 16);
		ft_nbr_upper_hex(num % 16);
	}
}

int	ft_putnbr_upper_hex(unsigned long num)
{
	int				i;
	unsigned long	num_cpt;

	num_cpt = num;
	i = 0;
	if (num == 0)
		i = 1;
	while (num_cpt != 0)
	{
		num_cpt /= 16;
		i++;
	}
	ft_nbr_upper_hex(num);
	return (i);
}

void	ft_nbr_hex(unsigned long num)
{
	if (num < 10)
		ft_putchar(num + 48);
	else if (num >= 10 && num < 16)
		ft_putchar(num + 'a' - 10);
	else
	{
		ft_nbr_hex(num / 16);
		ft_nbr_hex(num % 16);
	}
}

int	ft_putnbr_hex(unsigned long num)
{
	int				i;
	unsigned long	num_cpt;

	num_cpt = num;
	i = 0;
	if (num == 0)
		i = 1;
	while (num_cpt != 0)
	{
		num_cpt /= 16;
		i++;
	}
	ft_nbr_hex(num);
	return (i);
}
