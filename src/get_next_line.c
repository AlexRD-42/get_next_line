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

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	char	*odst;

	odst = dst;
	while (*dst != 0)
		dst++;
	while (*src != 0 && n > 0)
	{
		*dst++ = *src++;
		n--;
	}
	*dst = 0;
	return (odst);
}

void	*ft_realloc(void *old_array, size_t old_size, size_t new_size)
{
	void	*new_array;

	new_array = (void *) malloc (new_size);
	if (new_array != NULL)
		memcpy(new_array, old_array, old_size);
	free(old_array);
	return (new_array);
}

static ssize_t	ft_read(FILE *fd, t_buffer *buffer, ssize_t *start, char **str)
{
	ssize_t	bytes_read;
	
	if (buffer->pos == 0 || buffer->pos >= BUFFER_SIZE) // Only reads from the file if the buffer is full or first run
	{
		// bytes_read = read(fd, buffer->str, BUFFER_SIZE);
		bytes_read = fread(buffer->str, 1, BUFFER_SIZE, fd);
		buffer->pos = 0; // Resets position
	}
	else
		bytes_read = (buffer->str[buffer->pos]) != 0; // Checks for EOF and sets byte status accordingly
	if (bytes_read <= 0) // If EOF or error reading, set STR to NULL and return 0
	{
		*str = NULL;
		return (0);
	}
	else // If not EOF, allocate empty string
	{
		*str = (char *) malloc(1);
		if (*str == NULL)
			return (0);
		**str = 0;
	}
	*start = buffer->pos;
	return (bytes_read);
}

char	*get_next_line(FILE *fd)
{
	static	t_buffer	buffer = {0};
	ssize_t				start;
	size_t				old_len;
	size_t				len;
	char				*str;

	if (fd == NULL || BUFFER_SIZE <= 0)
		return (NULL);
	old_len = 1;
	while (ft_read(fd, &buffer, &start, &str) > 0) // This will only be false when EOF
	{
		while (buffer.pos < BUFFER_SIZE && buffer.str[buffer.pos] != '\n')
			buffer.pos++;
		len = old_len + buffer.pos - start;
		str = ft_realloc(str, old_len, len);
		if (str == NULL)
			return (NULL);
		str = ft_strncat(str, buffer.str + start, len);
		old_len = len;
		if (buffer.str[buffer.pos++] == '\n')
			return (str);
	}
	return (str);
}

int main()
{
	FILE *fd1 = fopen("test.txt", "r");
	// FILE *fd2 = fopen("test.txt", "r");
	printf("-%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	printf("%s-", get_next_line(fd1));
	fclose(fd1);
	// fclose(fd2);
	return(0);
}