/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:32:24 by ksudyn            #+#    #+#             */
/*   Updated: 2025/01/16 15:33:01 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pushswap.h"

static int	receive(char chr, va_list args)
{
	int	count;

	count = 0;
	if (chr == '%')
		count += ft_putchar_count('%', 1);
	else if (chr == 'c')
		count += ft_putchar_count(va_arg(args, int), 1);
	else if (chr == 's')
		count += ft_putstr_count(va_arg(args, char *), 1);
	else if (chr == 'd' || chr == 'i')
		count += ft_putnbr_combined_count(va_arg(args, int), 1, 0);
	else if (chr == 'u')
		count += ft_putnbr_combined_count(va_arg(args, unsigned int), 1, 1);
	else if (chr == 'x')
		count += ft_putnbr_hex_count(va_arg(args, unsigned int), 1, 0);
	else if (chr == 'X')
		count += ft_putnbr_hex_count(va_arg(args, unsigned int), 1, 1);
	else if (chr == 'p')
		count += ft_putaddress_count(va_arg(args, void *));
	else
		count += ft_putchar_count(chr, 1);
	return (count);
}

int	ft_printf(char	const *s, ...)
{
	va_list	arg;
	int		s_index;
	int		count;
	int		result;

	va_start(arg, s);
	s_index = 0;
	count = 0;
	while (s[s_index])
	{
		if (s[s_index] == '%')
		{
			s_index++;
			if (!s[s_index])
				break ;
			result = receive(s[s_index], arg);
			if (result == -1)
				return (va_end(arg), -1);
			count += result;
		}
		else
			count += ft_putchar_count(s[s_index], 1);
		s_index++;
	}
	return (va_end(arg), count);
}
