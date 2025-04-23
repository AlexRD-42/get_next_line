/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/23 12:47:11 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_read(int fd, char *buffer, t_position *pos, char **str)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	if (pos->end == 0)
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

uint8_t	ft_init(int fd, t_position *pos, char **str)
{
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (1);
	*str = NULL;
	pos->len = 0;
	pos->i = 0;
	pos->end = 0;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = {0};
	t_position	pos;
	char		*str;

	if (ft_init(fd, &pos, &str) == 1)
		return (NULL);
	while (ft_read(fd, buffer, &pos, &str) > 0)
	{
		while (pos.i < pos.end && buffer[pos.i] != '\n' && buffer[pos.i] != 0)
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
		if (*(str + pos.len - (pos.len > 0)) == '\n')
			break ;
	}
	return (str);
}
