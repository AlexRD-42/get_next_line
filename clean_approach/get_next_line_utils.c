/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:34:10 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/29 12:18:15 by adeimlin         ###   ########.fr       */
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

void	*ft_realloc(void *src, size_t src_size, size_t dst_size)
{
	void	*dst;

	dst = (void *) malloc (dst_size);
	if (dst != NULL)
	{
		*((unsigned char *) dst) = 0;
		if (src != NULL)
			ft_memcpy(dst, src, src_size);
	}
	free(src);
	return (dst);
}

ssize_t	ft_read(int fd, char *buffer, size_t *end, char **str)
{
	ssize_t	bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (*buffer == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(*str);
			*str = NULL;
		}
		else
			*end = (size_t) bytes_read;
	}
	else
	{
		bytes_read = 0;
		while (buffer[bytes_read] != 0)
			bytes_read++;
		*end = bytes_read;
	}
	return (bytes_read);
}
