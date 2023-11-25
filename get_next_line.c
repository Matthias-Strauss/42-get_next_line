/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:34:34 by mstrauss          #+#    #+#             */
/*   Updated: 2023/11/25 17:45:42 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_clean_up(char *tmp, char *buffer, char *final, int nl_index)
{
	// if (nl_index == 0)
	// {
	// 	free(final);
	// 	final = ft_strdup(tmp);
	// 	return (final);
	// }
	/*else if (nl_index)*/
	ft_strlcpy(buffer, &tmp[nl_index + 1], BUFFER_SIZE);
	ft_strlcpy(final, tmp, nl_index + 2);
	return (final);
}

char	*ft_get_more(char *tmp, char *buffer, int fd)
{
	char	*new;
	int		bytes_read;

	bytes_read = 1;
	if (!tmp)
		tmp = ft_calloc(1, sizeof(char));
	if (!tmp)
		return (NULL);
	new = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (bytes_read && ft_strchr(tmp, '\n') == -1)
	{
		bytes_read = read(fd, new, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_bzero(buffer, BUFFER_SIZE + 1), free(new), NULL);
		// if (bytes_read == 0)
		//	return (free(new), tmp);
		// new[BUFFER_SIZE] = '\0';
		new[bytes_read] = '\0';
		tmp = ft_strjoin(tmp, new);
		if (ft_strlen(tmp) == 0)
			return (free(new), free(tmp), NULL);
	}
	return (free(new), tmp);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*tmp;
	char		*final;
	int			nl_index;

	// int			nl_index;
	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[0] != 0)
	{
		tmp = ft_strdup(buffer);
		ft_bzero(buffer, BUFFER_SIZE);
	}
	else
		tmp = ft_calloc(1, 1);
	// if (ft_strchr(tmp, '\n') != 0)
	// IF BUFFER HAS '\n' on index=0 program fails!!!!!!!
	tmp = ft_get_more(tmp, buffer, fd);
	if (tmp == NULL)
		return (NULL);
	nl_index = ft_strchr(tmp, '\n');
	if ((nl_index == 0 && tmp[0] != '\n') || nl_index == -1)
		return (tmp);
	final = ft_calloc(nl_index + 2, sizeof(char));
	ft_clean_up(tmp, buffer, final, nl_index);
	// printf("\ntmp: %p\nbuffer: %p\nfinal: %p\n", tmp, buffer, final);
	return (free(tmp), final);
}
