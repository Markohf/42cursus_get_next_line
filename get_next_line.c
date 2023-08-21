/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco-fe <marco-fe@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:00:04 by marco-fe          #+#    #+#             */
/*   Updated: 2023/07/17 16:58:11 by marco-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**/

#include "get_next_line.h"

/**/
char	*ft_substr_gnl(char const *s, unsigned int start, size_t n)
{
	size_t	len_s;
	size_t	size;
	char	*dst;

	len_s = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= len_s)
		return (NULL);
	size = n + 1;
	if (start + n > len_s)
		size = len_s - start + 1;
	dst = malloc(size);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s + start, size);
	return (dst);
}

/**/
char	*read_file(char *buff_read, char *buff_stash, int fd)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff_read, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff_read);
			return (NULL);
		}
		buff_read[bytes_read] = '\0';
		if (buff_stash)
			buff_stash = ft_strjoin_gnl(buff_stash, buff_read);
		else
			buff_stash = ft_substr_gnl(buff_read, 0, ft_strlen(buff_read));
		if (buff_stash && ft_strchr(buff_stash, '\n'))
			bytes_read = 0;
	}
	free(buff_read);
	return (buff_stash);
}

/**/
char	*stash_clean(char *buff_stash)
{
	char	*new_stash;
	char	*position;

	position = ft_strchr(buff_stash, '\n');
	if (position)
	{
		position++;
		new_stash = ft_substr_gnl(position, 0, ft_strlen(position));
		free(buff_stash);
		return (new_stash);
	}
	free(buff_stash);
	return (NULL);
}

/**/
char	*create_line(char *buff_stash)
{
	size_t	size;
	char	*buff_line;

	if (ft_strchr(buff_stash, '\n'))
		size = ft_strchr(buff_stash, '\n') - buff_stash + 2;
	else
		size = ft_strlen(buff_stash) + 1;
	buff_line = ft_calloc_gnl(size, sizeof (char));
	if (!buff_line)
	{
		free(buff_stash);
		return (NULL);
	}
	ft_strlcpy(buff_line, buff_stash, size);
	return (buff_line);
}

/*Main function.*/
char	*get_next_line(int fd)
{
	char		*buff_read;
	static char	*buff_stash;
	char		*buff_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd > OPEN_MAX)
		return (NULL);
	buff_read = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof (char));
	if (!buff_read)
		return (NULL);
	buff_stash = read_file(buff_read, buff_stash, fd);
	if (!buff_stash)
	{
		free(buff_stash);
		return (NULL);
	}
	buff_line = create_line(buff_stash);
	buff_stash = stash_clean(buff_stash);
	return (buff_line);
}
