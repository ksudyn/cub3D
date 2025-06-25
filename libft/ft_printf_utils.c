/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:49:38 by ksudyn            #+#    #+#             */
/*   Updated: 2025/01/24 15:50:44 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pushswap.h"

int	ft_putchar_count(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr_count(char *s, int fd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
	{
		return (ft_putstr_count("(null)", fd));
	}
	while (s[i] != '\0')
	{
		count += write(fd, &s[i], 1);
		i++;
	}
	return (count);
}

int	ft_putnbr_combined_count(long long n, int fd, int is_unsigned)
{
	unsigned long long	nbr;
	int					count;

	count = 0;
	if (!is_unsigned && n < 0)
	{
		count += ft_putchar_count('-', fd);
		nbr = -n;
	}
	else
		nbr = (unsigned long long)n;
	if (nbr >= 10)
		count += ft_putnbr_combined_count(nbr / 10, fd, is_unsigned);
	count += ft_putchar_count ((nbr % 10) + '0', fd);
	return (count);
}

int	ft_putnbr_hex_count(unsigned long long n, int fd, int upcase)
{
	unsigned long long	nbr;
	int					count;
	char				*base;

	if (upcase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	count = 0;
	nbr = n;
	if (nbr >= 16)
		count += ft_putnbr_hex_count(nbr / 16, fd, upcase);
	count += ft_putchar_count(base[nbr % 16], fd);
	return (count);
}

int	ft_putaddress_count(void *ptr)
{
	unsigned long long	address;
	int					count;

	address = (unsigned long long)ptr;
	count = 0;
	if (address == 0)
		count += ft_putstr_count("(nil)", 1);
	else
	{
		count += ft_putstr_count("0x", 1);
		count += ft_putnbr_hex_count(address, 1, 0);
	}
	return (count);
}
