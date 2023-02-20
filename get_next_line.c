/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akapusti <akapusti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:38:11 by akapusti          #+#    #+#             */
/*   Updated: 2023/02/20 18:22:11 by akapusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char *read_buffer(int fd, int *bytes_read)
{
    char *buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
        return (NULL);
    *bytes_read = read(fd, buf, BUFFER_SIZE);
    if (*bytes_read < 0)
    {
        free(buf);
        return (NULL);
    }
    buf[*bytes_read] = '\0';
    return (buf);
}

static char *get_one_line(int fd)
{
    char *line = NULL;
    char *buf;
    int bytes_read;
    int total_bytes_read = 0;
    
    while (1)
    {
        buf = read_buffer(fd, &bytes_read);
        if (!buf)
            break;
        total_bytes_read += bytes_read;
        line = ft_strnjoin(line, buf, bytes_read);
        free(buf);
        if (!line)
            break;
        if (ft_strchr(line, '\n'))
            break;
    }
    if (line == NULL && total_bytes_read == 0)
        return (NULL);
    return (line);
}
