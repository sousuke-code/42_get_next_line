/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosmiyat <sosmiyat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:56:46 by sosmiyat          #+#    #+#             */
/*   Updated: 2024/12/15 16:16:45 by sosmiyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *c)
{
	size_t	count;

	count = 0;
	while (*c != '\0')
	{
		count++;
		c++;
	}
	return (count);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		i;
	int		len;

	len = 0;
	i = 0;
	len = ft_strlen((char *)s1);
	p = (char *)malloc(len + 1);
	if (p == NULL)
	{
		return (NULL);
	}
	while (*s1 != '\0')
	{
		p[i] = *s1;
		i++;
		s1++;
	}
	p[len] = '\0';
	return (p);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	max_cpy;
	size_t	n;

	n = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	max_cpy = dstsize - dst_len - 1;
	while (n < max_cpy && src[n] != '\0')
	{
		dst[dst_len + n] = src[n];
		n++;
	}
	dst[dst_len + n] = '\0';
	return (dst_len + src_len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	i;

	n = 0;
	while (src[n])
	{
		n++;
	}
	if (size == 0)
	{
		return (n);
	}
	i = 0;
	while (i < size - 1 && *src != '\0')
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	*dst = '\0';
	return (n);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = malloc(len);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, (char *)s1, ft_strlen((char *)s1) + 1);
	ft_strlcat(str, (char *)s2, len);
	return (str);
}
