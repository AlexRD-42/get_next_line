/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:03:00 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/23 18:05:10 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef FD_SIZE
#  define FD_SIZE 1024
# endif

# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct t_position
{
	size_t		i;
	size_t		len;
	size_t		end;
}	t_position;

char	*get_next_line(int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size);
void	*ft_memcpy(void *dst_void, const void *src_void, size_t n);
void	*ft_realloc(void *old_array, size_t old_size, size_t new_size);
ssize_t	ft_read(int fd, char *buffer, t_position *pos, char **str);
#endif