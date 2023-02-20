/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akapusti <akapusti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:38:29 by akapusti          #+#    #+#             */
/*   Updated: 2023/02/20 14:38:49 by akapusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	static char	*saved = NULL;
	char	*tmp;
	ssize_t	read_size;
	char	*newline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		if (saved == NULL)
			saved = strdup(buf);
		else
		{
			tmp = saved;
			saved = strjoin(saved, buf);
			free(tmp);
		}
		if ((newline = strchr(saved, '\n')))
			return (substr(&saved, 0, newline - saved));
	}
	if (read_size == -1)
		return (NULL);
	if (saved == NULL)
		return (NULL);
	newline = strchr(saved, '\0');
	tmp = saved;
	saved = substr(&saved, 0, newline - saved);
	free(tmp);
	return (saved);
}
