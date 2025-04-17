/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:40:56 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/17 20:00:03 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// Read from a big buffer (like 4096 bytes)
// Size the buffer to 64 cache lines
# define BUFFER_SIZE 4096

#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

// The return dictates the state of whether we need a new read
static char	*str = NULL;

int64_t	ft_read(int fd)
{
	uint8_t	*buffer[BUFFER_SIZE];

	if (fd == NULL)
		return (NULL);
	*(buffer + BUFFER_SIZE) = 0; // maybe better to use memset?
	return (read(fd, buffer, BUFFER_SIZE - 1));
}

char	*ft_get_next_line(char *str, int fd)
{
	if (fd == -1)
		return (NULL);
	bytes_read = 
	while (*str != '\n')
	{
		if (*str == 0)
			str = ft_read(fd);
		str++;
	}
	return (str);
}

