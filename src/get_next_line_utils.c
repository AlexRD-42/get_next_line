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

char	*ft_strjoin(char *src1, char *src2)
{
	const char	*osrc1 = src1;
	const char	*osrc2 = src2;
	char		*str;

	str = NULL;
	if (src1 != NULL && src2 != NULL)
	{
		while (*src1 != 0)
			src1++;
		while (*src2 != 0)
			src2++;
		str = (char *) malloc ((src1 - osrc1) + (src2 - osrc2) + 1);
		if (str == NULL)
			return (NULL);
		str += (src1 - osrc1) + (src2 - osrc2);
		*str = 0;
		while (src2 > osrc2)
			*--str = *--src2;
		while (src1 > osrc1)
			*--str = *--src1;
	}
	free(src1);
	free(src2);
	return (str);
}

