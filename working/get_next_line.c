/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/21 16:48:54 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static uint8_t	ft_init(int fd, char *buffer, t_position *pos, t_string *str)
{
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (1);
	str->data = NULL;
	str->len = 0;
	pos->diff = BUFFER_SIZE;
	pos->ptr = buffer;
	pos->end = buffer + BUFFER_SIZE;
	while (pos->ptr < pos->end && *(pos->ptr) == 0)
		pos->ptr++;
	pos->optr = pos->ptr;
	return (0);
}

static ssize_t	ft_read(int fd, char *buffer, t_position *pos, t_string *str)
{
	ssize_t	bytes_read;

	bytes_read = pos->diff >= BUFFER_SIZE;
	if (pos->ptr >= pos->end)
	{
		pos->ptr = buffer;
		pos->optr = buffer;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			ft_memset(buffer, 0, BUFFER_SIZE);
			free(str->data);
			str->data = NULL;
		}
	}
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = {0};
	t_position	pos;
	t_string	str;

	if (ft_init(fd, buffer, &pos, &str) == 1)
		return (NULL);
	while (ft_read(fd, buffer, &pos, &str) > 0)
	{
		while (pos.ptr < pos.end && *(pos.ptr) != '\n' && *(pos.ptr) != 0)
			pos.ptr++;
		if (pos.ptr < pos.end && *(pos.ptr) == '\n')
			pos.ptr++;
		pos.diff = pos.ptr - pos.optr;
		str.data = ft_realloc(str.data, str.len, str.len + pos.diff + 1);
		if (str.data == NULL)
			return (NULL);
		ft_strlcpy(str.data + str.len, pos.optr, pos.diff + 1);
		str.len += pos.diff;
		ft_memset(pos.optr, 0, pos.diff);
		if (*(str.data + str.len - (str.len > 0)) == '\n')
			break ;
	}
	return (str.data);
}
