/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 00:25:05 by mstrauss          #+#    #+#             */
/*   Updated: 2023/11/27 22:40:04 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

/// @brief Determines char string length
/// @param s String to measure
/// @return Length of string including Nul-terminator
int	ft_strlen(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = -1;
	while (s[++i] != '\0')
		;
	return (i);
}

/// @brief 	strlcpy() copies up to dstsize - 1 characters from the string src to
/// 		dst, NUL-terminating the result if dstsize is not 0.
/// @param dst			destination string
/// @param src			source string
/// @param dstsize		size of dst INCLUDING Nul-termination
/// @return				length of source
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	unsigned long	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

/// @brief 		Allocates (with malloc(3)) and returns a new
///				string, which is the result of the concatenation
///				of ’s1’ and ’s2’.
/// @param s1 	String 1
/// @param s2 	String 2
/// @return 	New composite String
///				NULL if the allocation fails.
char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = -1;
	j = -1;
	if (s1 == NULL)
		return (free(s2), NULL);
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ptr == NULL)
		return (free(s1), NULL);
	while (s1 && s1[++i])
		ptr[i] = s1[i];
	while (s2 && s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	free(s1);
	s1 = NULL;
	return (ptr);
}

/// @brief 		Allocates sufficient memory for a copy of the string s1,
/// 			does the copy, and returns a pointer to it.
/// @param s1 	String 1.
/// @return 	Pointer to allocated memory.
///				if fail; return NULL and set errno to ENOMEM.
char	*ft_strdup(char *s1)
{
	int		len;
	int		i;
	char	*ptr;

	len = ft_strlen(s1);
	i = -1;
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	while (++i <= len && s1[i])
		ptr[i] = s1[i];
	ptr[i] = '\0';
	return (ptr);
}

/// @brief Allocates (with malloc(3)) and returns a substring from the string s.
///			The substring begins at index ’start’ and is of maximum size ’len’.
/// @param s 		The string from which to create the substring.
/// @param start 	The start index of the substring in the string ’s’.
/// @param len 		The maximum length of the substring.
/// @return			The substring. NULL if the allocation fails.
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*dst;
	unsigned long	s_len;

	s_len = ft_strlen(s);
	if ((len == 0 || s_len == 0) || start >= s_len)
	{
		dst = ft_calloc(1, sizeof(char));
		if (dst == NULL)
			return (free(dst), free(s), NULL);
		*dst = '\0';
		return (dst);
	}
	else if (len > s_len - start)
	{
		dst = ft_calloc(s_len - start + 1, sizeof(char));
		if (dst == NULL)
			return (free(dst), free(s), NULL);
		len = s_len;
	}
	else
		dst = ft_calloc(len + 1, sizeof(char));
	if (dst == NULL)
		return (free(dst), free(s), NULL);
	ft_strlcpy(dst, &s[start], len + 1);
	return (dst);
}

/// @brief The strlcat() function concatenates strings
/// @param dst pointer to the destination string to be extended
/// @param src pointer to the source string to be copied over
/// @param dstsize size of the destination string INCLUDING '\0'
/// @return length of dst plus the length of src
size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	dst_len;

	i = 0;
	j = -1;
	dst_len = ft_strlen(dst);
	if (dstsize < dst_len || dstsize == 0)
		return (ft_strlen(src) + dstsize);
	while (dst[i] != '\0' && i < dstsize)
		i++;
	while (i + ++j < dstsize - 1 && src[j])
		dst[i + j] = src[j];
	dst[i + j] = '\0';
	return (dst_len + ft_strlen(src));
}

/// @brief 	Locates the FIRST occurrence of c (as a char)
///			in the string pointed to by s.
///			The terminating null character is considered to be part of the str
///			therefore if c is `\0', the functions locate the terminating `\0'
/// @param s	string to be searched.
/// @param c	character to search for.
/// @return		pointer to the located character, NULL if non found
int	ft_strchr(char *s, int c)
{
	int	i;

	if (s == NULL)
		return (0);
	i = -1;
	c = (char)c;
	if (s == NULL)
		return (0);
	while (s[++i] != '\0')
		if (s[i] == c)
			return (i);
	return (-1);
}

/// @brief writes n zeroed bytes to the string s
/// @param s string to be written to
/// @param n amount of bytes to be written
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*d;

	d = s;
	while (0 < n)
		d[n-- - 1] = 0;
}

/// @brief Contiguously allocates enough space for count objects
///			that are size bytes of memory filled with bytes of value zero
/// @param count amount of objects
/// @param size bytesize of an object
/// @return If successful calloc returns a pointer to allocated memory.
/// If there is an error, they return a NULL pointer and set errno to ENOMEM.
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	unsigned long	i;
	int				n;

	i = 0;
	n = count * size;
	ptr = NULL;
	ptr = malloc(n);
	if (ptr == NULL)
		return (NULL);
	while (0 < n)
		ptr[n-- - 1] = 0;
	return (ptr);
}
