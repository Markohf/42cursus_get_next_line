/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco-fe <marco-fe@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:00:07 by marco-fe          #+#    #+#             */
/*   Updated: 2023/07/17 16:15:06 by marco-fe         ###   ########.fr       */
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
	if (n > 0)
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

/*Changed to handle not existing s1.*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*new;

	size = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(size + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, ft_strlen(s1) + 1);
	ft_strlcpy(new + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (new);
}

void	*ft_calloc_gnl(unsigned int count, unsigned int size)
{
	unsigned int	tot;
	char			*buff;

	tot = count * size;
	buff = malloc(tot);
	if (!buff)
		return (NULL);
	while (tot)
		buff[--tot] = '\0';
	return (buff);
}