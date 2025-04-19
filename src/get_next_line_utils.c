/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:34:10 by adeimlin          #+#    #+#             */
/*   Updated: 2025/04/18 10:34:10 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Before substr is allocated, it is used as a temp variable to store
// the starting position of (str + start), to limit the max length
char	*ft_substr(const char *str, size_t start, size_t len)
{
	const char	*ostr = str;
	char		*substr;

	if (str == NULL)
		return (NULL);
	while (*str != 0)
		str++;
	substr = (char *) ostr + start;
	if (substr > str)
		return (NULL);
	if (substr + len > str)
		len = str - substr;
	str = substr + len;
	substr = (char *) malloc (len + 1);
	if (substr == NULL)
		return (NULL);
	substr += len;
	*substr = 0;
	while (len > 0)
	{
		*--substr = *--str;
		len--;
	}
	return (substr);
}

