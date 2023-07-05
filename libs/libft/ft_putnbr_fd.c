/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:28:39 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/08 14:36:06 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	putnbr(unsigned int n, int fd)
{
	unsigned int	nb;

	nb = n;
	if (n > 9)
		putnbr(n / 10, fd);
	ft_putchar_fd(nb % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	negative;

	negative = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		negative *= -1;
	}
	putnbr(n * negative, fd);
}
