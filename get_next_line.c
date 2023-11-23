/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:42:02 by mstrauss          #+#    #+#             */
/*   Updated: 2023/11/21 19:30:51 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_build_line(char *str, char *buffer, int fd)
{
	int		nl_index;
	char	*tmp;

	nl_index = 0;
	while (nl_index == 0)
	{
		nl_index = ft_strchr(str, '\n');
		if (nl_index != 0)
			break ;
		read(fd, buffer, BUFFER_SIZE);
		tmp = ft_strjoin(str, buffer);
		free(buffer);
		str = tmp;
	}
	tmp = ft_strdup(&buffer[nl_index]);
	free(buffer);
	buffer = tmp;
	tmp = ft_calloc(nl_index + 1, sizeof(char));
	ft_strlcpy(tmp, str, nl_index + 1);
	free(str);
	str = tmp;
	return (str);
}

/// @brief 	Reads from a filedescriptor until it reaches
/// 		a newline and returns the str
/// @param fd File descriptor to be read from
/// @return	On success: a complete next line of the file
///         On error: (null)
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*str;
	int			exit_check;

	exit_check = 0;
	if (buffer == NULL || fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer == NULL)
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (free(buffer), NULL);
	// if (!(buffer[0] == '\0'))
	str = ft_strdup(buffer);
	return (gnl_build_line(str, buffer, fd));
}

// check if buffer empty;
// 	empty - > continue normally
// 	full -> copy to str

// check str for nl
// nl -> trim str, first part stays in str, second part in buff
// no nl -> reallocate str and concatenate with fresh read()

// check value for nl_found exits while loop and executes return

// 2 CASES

// Case 1: buffer empty
// 	{read to str
// 	check str for nl}
// 	reapeat until nl found
// 	trim rest
// 	save rest in buff

// Case 2: buffer not empty
// 	copy from buff to str
// 	check for nl
// 		->rest to buff and return
// 		->no nl, continue reading
// 	reapeat until nl found
// 	trim rest
// 	save rest in buff
