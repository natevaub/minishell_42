/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:03:29 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/18 18:21:05 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include <unistd.h>
# include <stdarg.h>

int		ft_putchar(int c);
int		ft_putstr(const char *str);
int		ft_putnbr(int num);
void	ft_nbr_hex(unsigned long num);
int		ft_putnbr_hex(unsigned long num);
void	ft_nbr_upper_hex(unsigned long num);
int		ft_putnbr_upper_hex(unsigned long num);
int		vl_print(va_list vl, const char c);
int		ft_printf(const char *fmt, ...);

#endif