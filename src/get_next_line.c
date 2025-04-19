/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/19 21:43:07 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static inline ssize_t	ft_read(int fd, char buffer[BUFFER_SIZE], t_position *pos)
{
	ssize_t			bytes_read;

	bytes_read = pos->ptr - buffer;
	pos->end = buffer + BUFFER_SIZE;
	if (bytes_read >= BUFFER_SIZE)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		pos->ptr = buffer;
	}
	pos->start = pos->ptr;
	return (bytes_read);
}

// you can save position by setting what you've read so far to 0
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = {0};
	t_position	pos;
	t_length	len;
	char		*str;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	while (pos.ptr == 0)
		pos.ptr++;
	while (ft_read(fd, buffer, &pos) > 0)
	{
		while (pos.ptr != '\n' && pos.ptr < pos.end)
			pos.ptr++;
		len.new = pos.ptr - pos.start;
		str = ft_realloc(str, len.old, len.old + len.new + 1);
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, pos.start, len.new + 1);
		if (ft_is_end(&buffer) == 0)
			return(str);
	}
	free(str);
	return (NULL);
}

// int main()
// {
// 	int fd1 = open("test.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd1));
// 	close(fd1);
// 	// close(fd2);
// 	return(0);
// }