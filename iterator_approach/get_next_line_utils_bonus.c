/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:34:10 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/23 15:29:05 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	const char	*osrc = src;

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

void	*ft_memcpy(void *dst_void, const void *src_void, size_t size)
{
	char		*dst;
	const char	*src;

	dst = (char *) dst_void;
	src = (const char *) src_void;
	if (dst == src)
		return (dst_void);
	while (size > 0)
	{
		*dst++ = *src++;
		size--;
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
