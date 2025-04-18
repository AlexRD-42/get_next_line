#include <stddef.h>

char	*ft_strjoin(const char *src1, const char *src2)
{
	const char	*osrc1 = src1;
	const char	*osrc2 = src2;
	char		*str;
	size_t		len;

	if (src1 == NULL || src2 == NULL)
		return (NULL);
	while (*src1 != 0)
		src1++;
	while (*src2 != 0)
		src2++;
	len = (src1 - osrc1) + (src2 - osrc2);
	str = (char *) malloc (len + 1);
	if (str == NULL)
		return (NULL);
	str += len;
	*str = 0;
	while (src2 > osrc2)
		*--str = *--src2;
	while (src1 > osrc1)
		*--str = *--src1;
	return (str);
}

// ptr
char	*ft_substr(const char *str, size_t start, size_t len)
{
	const char	*ostr = str;
	char	*substr;

	if (str == NULL)
		return (NULL);
	while (*str != 0)
		str++;
	if (ostr + start > str)
		return (NULL);
	if (len > (str - ostr) - start)
		len = (str - ostr) - start;
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