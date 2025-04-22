/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:03:00 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/22 19:12:44 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_position
{
	char		*end;	// Points to the end of the buffer
	char		*ptr;	// Points to the current position (ends in 0 or nl)
	size_t		diff;	// How many characters were read
}	t_position;

typedef struct s_string
{
	char	*data;
	size_t	len;
}	t_string;

char	*get_next_line(int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size);
void	*ft_memcpy(void *dst_void, const void *src_void, size_t n);
void	*ft_realloc(void *old_array, size_t old_size, size_t new_size);
ssize_t	ft_read(int fd, char *buffer, t_position *pos, t_string *str);
uint8_t	ft_merge(char *buffer, t_position *pos, t_string *str);
#endif