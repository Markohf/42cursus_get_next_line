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

char	*read_file(int fd)
{
	char	*buff_mid;
	ssize_t	read_error;

	buff_mid = ft_calloc(BUFFER_SIZE + 1, sizeof (char));
	if (!buff_mid)
		return(NULL);
	read_error = read(fd, buff_mid, BUFFER_SIZE);
	if (read_error == -1)
		return (NULL);
	buff_mid[BUFFER_SIZE + 1] = '\0';
	return (buff_mid);
}

void	ind_validator(char *buff_mid)
{
	if (ft_strchr(buff_mid, '\n'))
		print_line();
	else 
}

char	*get_next_line(int fd)
{
	char	*buff_mid;
	char	*buff_end;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return(NULL);
	buff_mid = read_file(fd);
	if (!buff_mid)
		return(NULL);
	ind_validator(buff_mid);
}
