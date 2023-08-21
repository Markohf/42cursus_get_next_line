/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco-fe <marco-fe@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:00:07 by marco-fe          #+#    #+#             */
/*   Updated: 2023/08/18 10:53:04 by marco-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**/

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*p_s;
	char	c_c;

	p_s = (char *)s;
	c_c = (char)c;
	while (*p_s)
	{
		if (*p_s == c_c)
			return (p_s);
		p_s++;
	}
	if (c_c == 0)
		return (p_s);
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0 && src)
	{
		while (src[i] && i < n - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(len1 + len2 + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, len1 + 1);
	ft_strlcpy(new + len1, s2, len2 + 1);
	free((char *)s1);
	return (new);
}

void	*ft_calloc_gnl(unsigned int count, unsigned int size)
{
	unsigned int	tot;
	char			*buff;

	if (size > 0 && count > ULONG_MAX / size)
		return (NULL);
	tot = count * size;
	buff = malloc(tot);
	if (!buff)
		return (NULL);
	while (tot)
		buff[--tot] = '\0';
	return (buff);
}
