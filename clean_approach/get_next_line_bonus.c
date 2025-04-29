/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/29 12:25:53 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FD_SIZE][BUFFER_SIZE] = {0};
	char		*str;
	size_t		i;
	size_t		end;
	size_t		len;

	str = NULL;
	len = 0;
	while (ft_read(fd, buffer[fd], &end, &str) > 0)
	{
		i = 0;
		while (i < end && buffer[fd][i] != 0 && buffer[fd][i] != '\n')
			i++;
		i += (i < end && buffer[fd][i] == '\n');
		str = ft_realloc(str, len, len + i + 1);
		if (str == NULL)
			break ;
		ft_strlcpy(str + len, buffer[fd], i + 1);
		len += i;
		end -= i;
		ft_strlcpy(buffer[fd], buffer[fd] + i, end + 1);
		if (str[len - 1] == '\n')
			break ;
	}
	return (str);
}
