/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/23 13:49:57 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_read(int fd, char *buffer, t_position *pos, char **str)
{
	ssize_t	bytes_read;

	if (*str != NULL && (*(*str + pos->len - (pos->len > 0)) == '\n'))
		return (0);
	bytes_read = 1;
	if (*buffer == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(*str);
			*str = NULL;
		}
		else
		{
			pos->i = 0;
			pos->end = bytes_read;
		}
	}
	return (bytes_read);
}

// To create a function that merges and clear i need to:
// Pass str, i, len, end, buffer
// Don't think end is needed
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = {0};
	t_position	pos;
	char		*str;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	pos.i = 0;
	pos.len = 0;
	pos.end = BUFFER_SIZE;
	while (ft_read(fd, buffer, &pos, &str) > 0)
	{
		while (pos.i < pos.end && buffer[pos.i] != 0 && buffer[pos.i] != '\n')
			pos.i++;
		pos.i += (pos.i < pos.end && buffer[pos.i] == '\n');
		str = ft_realloc(str, pos.len, pos.len + pos.i + 1);
		if (str == NULL)
			break ;
		ft_strlcpy(str + pos.len, buffer, pos.i + 1);
		pos.len += pos.i;
		pos.end -= pos.i;
		ft_memcpy(buffer, buffer + pos.i, pos.end);
		*(buffer + pos.end) = 0;
	}
	return (str);
}
