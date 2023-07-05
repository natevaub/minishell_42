/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 02:02:17 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/08 14:34:17 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned int	intlen(int n)
{
	unsigned int	len;
	long			nbr;

	if (n == 0)
		return (1);
	len = 0;
	nbr = n;
	if (nbr < 0)
	{
		nbr = -nbr;
		len++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static	void	handle_negative(long *nbr, char **result)
{
	if (*nbr < 0)
	{
		*nbr *= -1;
		*result[0] = '-';
	}
}

char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	i;
	unsigned int	len;
	long			nbr;

	i = 0;
	len = intlen(n);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	nbr = n;
	handle_negative(&nbr, &result);
	if (nbr == 0)
		result[0] = '0';
	while (nbr != 0)
	{
		result[len - i - 1] = (nbr % 10) + '0';
		nbr /= 10;
		i++;
	}
	result[len] = 0;
	return (result);
}
