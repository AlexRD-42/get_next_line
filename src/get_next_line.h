/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:03:00 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/18 11:03:00 by adeimlin         ###   ########.fr       */
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

# define BUFFER_SIZE 1000

typedef struct	s_buffer
{
	char	str[BUFFER_SIZE];
	ssize_t	pos;
}	t_buffer;

char	*ft_substr(const char *str, size_t start, size_t len);
char	*ft_strjoin(char *src1, char *src2);
void	*ft_realloc(void *old_array, size_t old_size, size_t new_size);
#endif