/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:27:09 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/17 23:53:03 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	count_size(int num)
{
	int	i;

	i = 0;
	if (num >= 0 && num < 10)
		return (1);
	if (num < 0)
		i++;
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

unsigned int	count_unsigned_size(unsigned int num)
{
	unsigned int	i;

	i = 0;
	if (num < 10)
		return (1);
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}
