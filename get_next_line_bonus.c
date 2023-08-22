/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco-fe <marco-fe@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:00:04 by marco-fe          #+#    #+#             */
/*   Updated: 2023/07/17 16:58:11 by marco-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This program returns a string with a single line from a text file
each time it is called. The length of the line does not matter.
The string includes the line break if the line contains one.*/

#include "get_next_line_bonus.h"

/*Creates a sub string of "s", of "n" bytes long, starting at start and
allocates it in a new memory space. Returns a pointer to the new memory
direction.*/
char	*ft_substr_gnl(char const *s, unsigned int start, size_t n)
{
	size_t	len_s;
	size_t	size;
	char	*dst;

	len_s = ft_strlen_gnl(s);
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

/*Reads "BUFFER_SIZE" bytes of a file and save them in "buff_stash" until finds
the end of the file or a break line.*/
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
			free(buff_stash);
			buff_stash = NULL;
			return (NULL);
		}
		buff_read[bytes_read] = '\0';
		if (buff_stash)
			buff_stash = ft_strjoin_gnl(buff_stash, buff_read);
		else
			buff_stash = ft_substr_gnl(buff_read, 0, ft_strlen_gnl(buff_read));
		if (buff_stash && ft_strchr_gnl(buff_stash, '\n'))
			bytes_read = 0;
	}
	free(buff_read);
	return (buff_stash);
}

/*Cleans the static variable "buff_stash". If the variable includes a line
break, it retains the bytes after the line break for future calls to the 
program.*/
char	*stash_clean(char *buff_stash)
{
	char	*new_stash;
	char	*position;

	position = ft_strchr_gnl(buff_stash, '\n');
	if (position)
	{
		new_stash = ft_substr_gnl(position, 1, ft_strlen_gnl(position) - 1);
		free(buff_stash);
		return (new_stash);
	}
	free(buff_stash);
	return (NULL);
}

/*Creates the string that will be return by the program.*/
char	*create_line(char *buff_stash)
{
	size_t	size;
	char	*buff_line;

	if (ft_strchr_gnl(buff_stash, '\n'))
		size = ft_strchr_gnl(buff_stash, '\n') - buff_stash + 2;
	else
		size = ft_strlen_gnl(buff_stash) + 1;
	buff_line = ft_calloc_gnl(size, sizeof (char));
	if (!buff_line)
	{
		free(buff_stash);
		return (NULL);
	}
	ft_strlcpy(buff_line, buff_stash, size);
	return (buff_line);
}

/*Principal function.*/
char	*get_next_line(int fd)
{
	char		*buff_read;
	static char	*buff_stash[OPEN_MAX];
	char		*buff_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	buff_read = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof (char));
	if (!buff_read)
		return (NULL);
	buff_stash[fd] = read_file(buff_read, buff_stash[fd], fd);
	if (!buff_stash[fd])
		return (NULL);
	buff_line = create_line(buff_stash[fd]);
	if (buff_stash[fd])
		buff_stash[fd] = stash_clean(buff_stash[fd]);
	return (buff_line);
}
