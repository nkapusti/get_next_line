/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akapusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:40:41 by akapusti          #+#    #+#             */
/*   Updated: 2023/02/20 14:41:52 by akapusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"	

static char	*get_one_line(int fd, char *stash)
{
	char				*buf;
	int					bytes_read;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (42)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			if (stash)
				free(stash);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup(buf);
		else
			stash = ft_strjoin(stash, buf);
		if (ft_strchr(stash, '\n') || bytes_read == 0)
			break ;
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char			*stash;
	char				*temp;
	char				*line;
	int					len;

	if (fd < 0 || fd > FD_SETSIZE)
	{
		if (stash)
			free(stash);
		return (NULL);
	}
	stash = get_one_line(fd, stash);
	if (!stash)
		return (NULL);
	len = ft_strchr(stash, '\n') - stash;
	line = ft_substr(stash, 0, len + 1);
	temp = stash;
	stash = ft_substr(stash, len + 1, (ft_strlen(stash) - len));
	free(temp);
	return (line);
}
