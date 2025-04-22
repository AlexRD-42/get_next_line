/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:34:10 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/22 19:15:55 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	char const	*osrc = src;

	while (*src != 0 && dst_size > 1)
	{
		*dst++ = *src++;
		dst_size--;
	}
	if (dst_size != 0)
		*dst = 0;
	while (*src != 0)
		src++;
	return (src - osrc);
}

void	*ft_memcpy(void *dst_void, const void *src_void, size_t n)
{
	char		*dst;
	const char	*src;

	dst = (char *) dst_void;
	src = (const char *) src_void;
	if (dst == src)
		return (dst_void);
	while (n > 0)
	{
		*dst++ = *src++;
		n--;
	}
	return (dst_void);
}

void	*ft_realloc(void *old_array, size_t old_size, size_t new_size)
{
	void	*new_array;

	new_array = (void *) malloc (new_size);
	if (new_array != NULL)
	{
		*((unsigned char *) new_array) = 0;
		if (old_array != NULL)
			ft_memcpy(new_array, old_array, old_size);
	}
	free(old_array);
	return (new_array);
}

ssize_t	ft_read(int fd, char *buffer, t_position *pos, t_string *str)
{
	ssize_t	bytes_read;

	bytes_read = pos->diff >= BUFFER_SIZE;
	if (pos->ptr >= pos->end || *buffer == 0)
	{
		pos->ptr = buffer;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(str->data);
			str->data = NULL;
		}
		else
			pos->end = buffer + bytes_read;
	}
	return (bytes_read);
}

uint8_t	ft_merge(char *buffer, t_position *pos, t_string *str)
{
	pos->diff = pos->ptr - buffer;
	str->data = ft_realloc(str->data, str->len, str->len + pos->diff + 1);
	if (str->data == NULL)
		return (1);
	ft_strlcpy(str->data + str->len, buffer, pos->diff + 1);
	str->len += pos->diff;
	pos->end -= pos->diff;
	ft_memcpy(buffer, pos->ptr, pos->end - buffer);
	*(pos->end) = 0;
	return (*(str->data + str->len - (str->len > 0)) == '\n');
}
