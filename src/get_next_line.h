/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:03:00 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/21 13:57:17 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

typedef struct	s_position
{
	const char	*end;
	char		*optr;
	char		*ptr;
	size_t		diff;
}	t_position;

typedef struct	s_string
{
	char	*data;
	size_t	len;
}	t_string;

char	*get_next_line(int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size);
void	*ft_memcpy(void *dst_void, const void *src_void, size_t n);
void	*ft_realloc(void *old_array, size_t old_size, size_t new_size);
void	*ft_memset(void *dst_void, uint8_t byte, size_t n);
#endif