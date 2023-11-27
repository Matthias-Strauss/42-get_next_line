/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:34:34 by mstrauss          #+#    #+#             */
/*   Updated: 2023/11/27 22:37:02 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_clean_up(char *tmp, char *buffer, char *final, int nl_index)
{
	ft_strlcpy(buffer, &tmp[nl_index + 1], BUFFER_SIZE);
	ft_strlcpy(final, tmp, nl_index + 2);
	return (final);
}

char	*ft_get_more(char *tmp, char *buffer, int fd)
{
	char	*new;
	int		bytes_read;

	bytes_read = 1;
	if (tmp == NULL)
		tmp = ft_calloc(1, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	new = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (new == NULL)
		return (free(tmp), NULL);
	while (bytes_read && ft_strchr(tmp, '\n') == -1)
	{
		bytes_read = read(fd, new, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_bzero(buffer, BUFFER_SIZE), ft_bzero(new, BUFFER_SIZE),
				free(new), NULL);
		new[bytes_read] = '\0';
		tmp = ft_strjoin(tmp, new);
		if (tmp == NULL)
			return (free(new), free(tmp), NULL);
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

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (ft_bzero(buffer, BUFFER_SIZE + 1), NULL);
	tmp = ft_strdup(buffer);
	if (tmp == NULL)
		return (NULL);
	ft_bzero(buffer, BUFFER_SIZE);
	tmp = ft_get_more(tmp, buffer, fd);
	if (tmp == NULL)
		return (NULL);
	nl_index = ft_strchr(tmp, '\n');
	if ((nl_index == 0 && tmp[0] != '\n') || nl_index == -1)
		return (tmp);
	final = ft_calloc(nl_index + 2, sizeof(char));
	if (final == NULL)
		return (free(tmp), NULL);
	ft_clean_up(tmp, buffer, final, nl_index);
	return (free(tmp), final);
}
