/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:16:23 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/10 15:17:38 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	lens1;
	size_t	lens2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!s1 && !s2)
		return (NULL);
	dst = ft_calloc(lens1 + lens2 + 1, sizeof(char));
	if (!dst)
		return (NULL);
	while (s1[i++])
		ft_memcpy(dst, s1, lens1);
	while (s2[j++])
		ft_memcpy(lens1 + dst, s2, lens2);
	return (dst);
}
