/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidot <cvidot@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:52:29 by cvidot            #+#    #+#             */
/*   Updated: 2023/07/10 16:11:31 by cvidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*next_line(char *str)
{
	int		i;
	char	*buf;

	if (!str || !str[0])
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	buf = (char *)malloc((sizeof(char) * i) + 1);
	if (!buf)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		buf[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		buf[i++] = '\n';
	buf[i] = '\0';
	return (buf);
}

char	*remove_first_line(char *str)
{
	char	*buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	if (str[i] == '\n')
		i++;
	buf = (char *)malloc(ft_strlen(str) - i + 1);
	while (str[i])
		buf[j++] = str[i++];
	buf[j] = '\0';
	free(str);
	return (buf);
}

char	*read_file(int fd, char *input_str, char *buf)
{
	int		read_bytes;
	char	*tmp;

	read_bytes = 1;
	while (!(ft_strchr(input_str, '\n')) && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			free(input_str);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		tmp = ft_strjoin(input_str, buf);
		free(input_str);
		input_str = tmp;
	}
	free(buf);
	return (input_str);
}

char	*get_next_line(int fd)
{
	static char	*input_str;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (!buf)
		return (NULL);
	input_str = read_file(fd, input_str, buf);
	if (!input_str)
		return (NULL);
	buf = next_line(input_str);
	input_str = remove_first_line(input_str);
	return (buf);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
	}
	return (0);
}
