/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/21 13:09:14 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	char const	*osrc = src;

	while (*src != 0 && dst_size > 1)
	{
		*dst++ = *src++;
		dst_size--;
	}
	if (dst_size != 0)
		*dst = 0;
	while (*src != 0)
		src++;
	return (src - osrc);
}

void	*ft_memcpy(void *dst_void, const void *src_void, size_t n)
{
	char		*dst;
	const char	*src;

	dst = (char *) dst_void;
	src = (const char *) src_void;
	if (dst == src)
		return (dst_void);
	while (n > 0)
	{
		*dst++ = *src++;
		n--;
	}
	return (dst_void);
}

// Reallocates memory to a bigger size, copies old array
// If the old array is NULL, this is effectively just malloc
void	*ft_realloc(void *old_array, size_t old_size, size_t new_size)
{
	void	*new_array;

	new_array = (void *) malloc (new_size);
	if (new_array != NULL)
	{
		*((unsigned char *) new_array) = 0;
		if (old_array != NULL)
			ft_memcpy(new_array, old_array, old_size);
	}
	free(old_array);
	return (new_array);
}

static inline ssize_t	ft_read(int fd, t_buffer *buffer, t_length *len)
{
	ssize_t	bytes_read;

	if (buffer->pos == 0 || buffer->pos >= BUFFER_SIZE) // Only reads from the file if the buffer is full or first run
	{
		bytes_read = read(fd, buffer->str, BUFFER_SIZE);
		buffer->pos = 0; // Resets position
	}
	else
		bytes_read = (buffer->str[buffer->pos]) != 0; // Checks for EOF and sets byte status accordingly
	len->start = buffer->pos;
	len->new = 0;
	return (bytes_read);
}

static inline uint8_t	ft_is_end(t_buffer *buffer)
{
	uint8_t	value;

	value = buffer->pos < BUFFER_SIZE;
	value = value && (buffer->str[buffer->pos] != '\n');
	value = value && (buffer->str[buffer->pos] != 0);
	if (value != 0)
		buffer->pos++;
	return (value);
}

char	*get_next_line(int fd)
{
	static	t_buffer	buffer = {0};
	t_length			len;
	char				*str;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	len.old = 0;
	while (ft_read(fd, &buffer, &len) > 0) // This will only be false when EOF
	{
		while (ft_is_end(&buffer))
			len.new++;
		len.new += buffer.str[buffer.pos++] == '\n';
		str = ft_realloc(str, len.old, len.old + len.new + 1);
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str + len.old, buffer.str + len.start, len.new + 1);
		len.old += len.new;
		if (ft_is_end(&buffer) == 0)
			return(str);
	}
	// free(str);	// removing this might solve other issues
	return (NULL);
}

/*int main()
{
	int fd1 = open("../files/normal.txt", O_RDONLY);
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd1));
	close(fd1);
	// close(fd2);
	return(0);
}*/
