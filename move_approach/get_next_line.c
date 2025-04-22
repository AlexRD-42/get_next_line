/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/22 19:18:06 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = {0};
	t_position	pos;
	t_string	str;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	str.data = NULL;
	str.len = 0;
	pos.ptr = buffer;
	pos.end = buffer + BUFFER_SIZE;
	pos.diff = BUFFER_SIZE;
	while (ft_read(fd, buffer, &pos, &str) > 0)
	{
		while (pos.ptr < pos.end && *(pos.ptr) != '\n' && *(pos.ptr) != 0)
			pos.ptr++;
		if (pos.ptr < pos.end && *(pos.ptr) == '\n')
			pos.ptr++;
		if (ft_merge(buffer, &pos, &str) == 1)
			break ;
	}
	return (str.data);
}
