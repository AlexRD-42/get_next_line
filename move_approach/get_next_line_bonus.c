/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/22 11:00:08 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static uint8_t	ft_init(int fd, char *buffer, t_position *pos, t_string *str)
{
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (1);
	str->data = NULL;
	str->len = 0;
	pos->diff = BUFFER_SIZE;
	pos->ptr = buffer;
	pos->end = buffer + BUFFER_SIZE;
	return (0);
}

static ssize_t	ft_read(int fd, char *buffer, t_position *pos, t_string *str)
{
	ssize_t	bytes_read;

	bytes_read = pos->diff >= BUFFER_SIZE;
	if (pos->ptr >= pos->end || *buffer == 0)
	{
		pos->ptr = buffer;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			ft_memset(buffer, 0, BUFFER_SIZE);
			free(str->data);
			str->data = NULL;
		}
		else
			pos->end = buffer + bytes_read;
	}
	return (bytes_read);
}

static uint8_t	ft_merge(char *buffer, t_position *pos, t_string *str)
{
	pos->diff = pos->ptr - buffer;
	str->data = ft_realloc(str->data, str->len, str->len + pos->diff + 1);
	if (str->data == NULL)
		return (1);
	ft_strlcpy(str->data + str->len, buffer, pos->diff + 1);
	str->len += pos->diff;
	pos->end -= pos->diff;
	ft_memmove(buffer, pos->ptr, pos->end - buffer);
	*(pos->end) = 0;
	return (*(str->data + str->len - (str->len > 0)) == '\n');
}

char	*get_next_line(int fd)
{
	static char	buffer[FD_LIMIT][BUFFER_SIZE] = {0};
	t_position	pos;
	t_string	str;

	if (ft_init(fd, buffer[fd], &pos, &str) == 1)
		return (NULL);
	while (ft_read(fd, buffer[fd], &pos, &str) > 0)
	{
		while (pos.ptr < pos.end && *(pos.ptr) != '\n' && *(pos.ptr) != 0)
			pos.ptr++;
		if (pos.ptr < pos.end && *(pos.ptr) == '\n')
			pos.ptr++;
		if (ft_merge(buffer[fd], &pos, &str) == 1)
			break ;
	}
	return (str.data);
}
