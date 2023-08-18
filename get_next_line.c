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
char	*read_file(char *buff_stash, int fd)
{
	char	*buff_read;
	ssize_t	bytes_read;

	buff_read = ft_calloc_gnl(BUFFER_SIZE, sizeof (char));
	if (!buff_read)
		return (NULL);
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
		buff_stash = ft_strjoin(buff_stash, buff_read);
		if (ft_strchr(buff_stash, '\n') != NULL)
			bytes_read = 0;
	}
	free (buff_read);
	return (buff_stash);
}

/**/
static char	*stash_clean(char *buff_stash)
{
	char	*new_stash;
	char	*position;

	position = ft_strchr(buff_stash, '\n') + 1;
	if (!position)
	{
		free(buff_stash);
		return (NULL);
	}
	new_stash = ft_calloc_gnl(1, sizeof (char));
	new_stash = ft_strjoin(new_stash, position);
	free(buff_stash);
	return (new_stash);
}

/*Main function.*/
char	*get_next_line(int fd)
{
	static char	*buff_stash;
	char		*buff_line;
	size_t		size;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!buff_stash)
	{
		buff_stash = ft_calloc_gnl(1, sizeof (char));
		if (!buff_stash)
			return (NULL);
	}
	buff_stash = read_file(buff_stash, fd);
	/*if (!buff_stash)
	{
		free(buff_stash);
		return (NULL);
	}*/
	size = ft_strchr(buff_stash, '\n') - buff_stash + 2;
	buff_line = ft_calloc_gnl(size, sizeof (char));
	if (!buff_line)
		return (NULL);
	ft_strlcpy(buff_line, buff_stash, size);
	buff_stash = stash_clean(buff_stash);
	return (buff_line);
}
