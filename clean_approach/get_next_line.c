/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/29 12:21:16 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = {0};
	char		*str;
	size_t		i;
	size_t		end;
	size_t		len;

	str = NULL;
	len = 0;
	while (ft_read(fd, buffer, &end, &str) > 0)
	{
		i = 0;
		while (i < end && buffer[i] != 0 && buffer[i] != '\n')
			i++;
		i += (i < end && buffer[i] == '\n');
		str = ft_realloc(str, len, len + i + 1);
		if (str == NULL)
			break ;
		ft_strlcpy(str + len, buffer, i + 1);
		len += i;
		end -= i;
		ft_strlcpy(buffer, buffer + i, end + 1);
		if (str[len - 1] == '\n')
			break ;
	}
	return (str);
}
