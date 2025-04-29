/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/29 09:58:33 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = {0};
	t_position	pos;
	char		*str;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	pos.i = 0;
	pos.len = 0;
	pos.end = BUFFER_SIZE;
	while (ft_read(fd, buffer, &pos, &str) > 0)
	{
		while (pos.i < pos.end && buffer[pos.i] != 0 && buffer[pos.i] != '\n')
			pos.i++;
		pos.i += (pos.i < pos.end && buffer[pos.i] == '\n');
		str = ft_realloc(str, pos.len, pos.len + pos.i + 1);
		if (str == NULL)
			break ;
		ft_strlcpy(str + pos.len, buffer, pos.i + 1);
		pos.len += pos.i;
		pos.end -= pos.i;
		ft_memcpy(buffer, buffer + pos.i, pos.end);
		*(buffer + pos.end) = 0;
	}
	return (str);
}
