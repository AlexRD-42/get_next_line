/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/23 18:04:45 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buf[FD_SIZE][BUFFER_SIZE] = {0};
	t_position	pos;
	char		*str;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	pos.i = 0;
	pos.len = 0;
	pos.end = BUFFER_SIZE;
	while (ft_read(fd, buf[fd], &pos, &str) > 0)
	{
		while (pos.i < pos.end && buf[fd][pos.i] && buf[fd][pos.i] != '\n')
			pos.i++;
		pos.i += (pos.i < pos.end && buf[fd][pos.i] == '\n');
		str = ft_realloc(str, pos.len, pos.len + pos.i + 1);
		if (str == NULL)
			break ;
		ft_strlcpy(str + pos.len, buf[fd], pos.i + 1);
		pos.len += pos.i;
		pos.end -= pos.i;
		ft_memcpy(buf[fd], buf[fd] + pos.i, pos.end);
		*(buf[fd] + pos.end) = 0;
	}
	return (str);
}
