/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/18 11:07:58 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static inline ssize_t	ft_read(FILE *fd, t_buffer *buffer, ssize_t *start)
{
	ssize_t	bytes_read;

	// Only reads if first run, or exceeded the buffer
	if (buffer->pos == 0 || buffer->pos >= BUFFER_SIZE)
	{
		// bytes_read = read(fd, buffer->str, BUFFER_SIZE);
		bytes_read = fread(buffer->str, 1, BUFFER_SIZE, fd);
		buffer->pos = 0;
	}
	else
		bytes_read = 1;
	*start = buffer->pos;
	return (bytes_read);
}

char	*get_next_line(FILE *fd)
{
	static	t_buffer	buffer[1024];
	ssize_t				start;
	char				*ret_str;

	if (fd == NULL || BUFFER_SIZE <= 0)
		return (NULL);
	ret_str = (char *) malloc(1);
	if (ret_str == NULL)
		return (NULL);
	*ret_str = 0;
	while (ft_read(fd, &(buffer[fileno(fd)]), &start) > 0) // This will only be false when EOF
	{
		while ((buffer[fileno(fd)]).pos < BUFFER_SIZE && (buffer[fileno(fd)]).str[(buffer[fileno(fd)]).pos] != '\n')
			(buffer[fileno(fd)]).pos++;
		ret_str = ft_strjoin(ret_str, ft_substr((buffer[fileno(fd)]).str, start, (buffer[fileno(fd)]).pos - start + 1));
		if ((buffer[fileno(fd)]).str[(buffer[fileno(fd)]).pos++] == '\n')
			return (ret_str);
	}
	return (ret_str);
}

int main()
{
	FILE *fd1 = fopen("test.txt", "r");
	FILE *fd2 = fopen("test.txt", "r");
	printf("-%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd2));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd2));
	printf("%s-", get_next_line(fd2));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd2));
	fclose(fd1);
	fclose(fd2);
	return(0);
}