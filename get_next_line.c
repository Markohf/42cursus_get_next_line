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
	ssize_t	read_error;
	int		ctrl;
	char	*ind;

	buff_read = ft_calloc_gnl(BUFFER_SIZE, sizeof (char));
	if (!buff_read)
		return (NULL);
	ctrl = 1;
	while (ctrl == 1)
	{
		read_error = read(fd, buff_read, BUFFER_SIZE);
		if (read_error == -1)
		{
			free(buff_read);
			return (NULL);
		}
		buff_stash = ft_strjoin(buff_stash, buff_read);
		ind = ft_strchr(buff_stash, '\n');
		if (ind >= buff_stash)
			ctrl = 0;
	}
	free (buff_read);
	return (buff_stash);
}

/**/
char	*stash_clean(char *buff_stash)
{
	char	*new_stash;

	new_stash = ft_calloc_gnl(1, sizeof (char));
	//prueba
	printf("new_stash:\t%s\n", new_stash);
	new_stash = ft_strjoin(new_stash, ft_strchr(buff_stash, '\n') + 1);
	//prueba
	printf("new_stash:\t%s\n", new_stash);
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
		return(NULL);
	if (!buff_stash)
	{
		buff_stash = ft_calloc_gnl(1, sizeof (char));
		if (!buff_stash)
			return(NULL);
	}
	buff_stash = read_file(buff_stash, fd);
	size = ft_strchr(buff_stash, '\n') - buff_stash + 2;
	buff_line = ft_calloc_gnl(size, sizeof (char));
	if (!buff_line)
		return (NULL);
	ft_strlcpy(buff_line, buff_stash, size);
	buff_stash = stash_clean(buff_stash);
	//prueba
	printf("buff_stash:\t%s\n", buff_stash);
	return (buff_line);
}
/*como limpiar el stash, como manejar cuando se llega al final del texto y tener cuidado con que \n + 1 exista.*/