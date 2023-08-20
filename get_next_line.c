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

	buff_read = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof (char));
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
		buff_stash = ft_strjoin_gnl(buff_stash, buff_read);
		if (ft_strchr(buff_stash, '\n'))
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
	if (position && ++position)
	{
		new_stash = ft_strjoin_gnl(new_stash, position);
		free(buff_stash);
		return (new_stash);
	}
	free(buff_stash);
	return (NULL);
}

/*Main function.*/
char	*get_next_line(int fd)
{
	static char	*buff_stash;
	char		*buff_line;
	size_t		size;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buff_stash = read_file(buff_stash, fd);
	if (!buff_stash)
		return (NULL);
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
	buff_stash = stash_clean(buff_stash);
	return (buff_line);
}
