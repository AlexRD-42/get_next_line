/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/21 15:45:45 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	ft_read(int fd, char *buffer, t_position *pos)
{
	ssize_t	bytes_read;

	if (pos->ptr >= pos->end)
	{
		pos->ptr = buffer;
		pos->optr = buffer;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			ft_memset(buffer, 0, BUFFER_SIZE);
		return (bytes_read);
	}
	if (pos->diff < BUFFER_SIZE)
		return (0);
	return (1);
}

// optr is a pointer to the first char of the newline
static uint8_t	ft_init(int fd, char *buffer, t_position *pos, t_string *str)
{
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (1);
	str->data = NULL;
	str->len = 0;
	pos->diff = BUFFER_SIZE;
	pos->ptr = buffer;
	pos->end = buffer + BUFFER_SIZE;
	while (pos->ptr < pos->end && *(pos->ptr) == 0)
		pos->ptr++;
	pos->optr = pos->ptr;
	return (0);
}

// Things to keep in mind: empty files, 1 char files, only NL files
// You can save position by setting what you've read so far to 0
// pos will go through zeroes, and break
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = {0};
	t_position	pos;
	t_string	str;
	uint8_t		exit;

	exit = 0;
	if (ft_init(fd, buffer, &pos, &str) == 1)
		return (NULL);
	while (ft_read(fd, buffer, &pos) > 0)
	{
		while (pos.ptr < pos.end && *(pos.ptr) != '\n' && *(pos.ptr) != 0)
			pos.ptr++;
		if (pos.ptr < pos.end && *(pos.ptr) == '\n')
		{
			exit = 1;
			pos.ptr++;
		}
		pos.diff = pos.ptr - pos.optr;
		str.data = ft_realloc(str.data, str.len, str.len + pos.diff + 1);
		if (str.data == NULL)
			return (NULL);
		ft_strlcpy(str.data + str.len, pos.optr, pos.diff + 1);
		str.len += pos.diff;
		ft_memset(pos.optr, 0, pos.diff);
		if (exit == 1)
			break;
	}
	return (str.data); 	// If there is no next line, should i return optr until EOF?
}						// It might be better to break from loop and always return str if so

// int main()
// {
// 	int fd1 = open("../files/giant_line.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd1));
// 	close(fd1);
// 	return(0);
// }