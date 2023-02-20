/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akapusti <akapusti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:38:11 by akapusti          #+#    #+#             */
/*   Updated: 2023/02/20 17:38:52 by akapusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*buffer;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = NULL;
	bytes_read = 1;
	while (!line && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		saved = saved ? saved : strdup("");
		saved = strjoin(saved, buffer);
		if (strchr(saved, '\n'))
			line = substr(saved, 0, strchr(saved, '\n') - saved);
	}
	free(buffer);
	if (bytes_read == -1 || !line)
		return (NULL);
	if (line && strchr(saved, '\n'))
		saved = substr(saved, strchr(saved, '\n') - saved + 1, strlen(saved));
	else
		saved = NULL;
	return (line);
}
