/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:12:12 by grmullin          #+#    #+#             */
/*   Updated: 2025/05/28 18:11:33 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_check_line(char *file_reader)
{
	if (!file_reader)
	{
		file_reader = (char *)malloc(sizeof(char));
		if (!file_reader)
			return (NULL);
		file_reader[0] = '\0';
	}
	return (file_reader);
}

char	*read_and_append(int fd, char *file_reader)
{
	char	*store_line;
	char	*temp;
	ssize_t	bytes_read;

	file_reader = ft_check_line(file_reader);
	bytes_read = 1;
	while (!ft_strchr(file_reader, '\n') && bytes_read != 0)
	{
		store_line = (char *)malloc(BUFFER_SIZE + 1);
		if (!store_line)
			return (free(file_reader), NULL);
		bytes_read = read(fd, store_line, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(file_reader), free(store_line), NULL);
		store_line[bytes_read] = '\0';
		temp = ft_strjoin(file_reader, store_line);
		free(file_reader);
		file_reader = temp;
		free(store_line);
	}
	return (file_reader);
}

char	*ft_get_line(char *file_reader)
{
	char	*get_line;
	int		i;

	i = 0;
	if (!file_reader[i])
		return (NULL);
	while (file_reader[i] != '\0' && file_reader[i] != '\n')
		i++;
	get_line = (char *)malloc(i + 2);
	if (!get_line)
		return (NULL);
	i = 0;
	while (file_reader[i] != '\0' && file_reader[i] != '\n')
	{
		get_line[i] = file_reader[i];
		i++;
	}
	if (file_reader[i] == '\n')
	{
		get_line[i] = '\n';
		get_line[i + 1] = '\0';
	}
	else 
		get_line[i] = '\0';
	return (get_line);
}

char	*restart_buffer(char *file_reader)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	while (file_reader[i] != '\0' && file_reader[i] != '\n')
		i++;
	if (!file_reader[i])
	{
		free(file_reader);
		return (NULL);
	}
	new_line = (char *)malloc(sizeof(char) * (ft_strlen(file_reader) - i + 1));
	if (!new_line)
		return (NULL);
	i += 1;
	j = 0;
	while (file_reader[i])
		new_line[j++] = file_reader[i++];
	new_line[j] = '\0';
	free(file_reader);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*file_reader = NULL;
	char		*get_line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	file_reader = read_and_append(fd, file_reader);
	if (!file_reader)
		return (NULL);
	get_line = ft_get_line(file_reader);
	file_reader = restart_buffer(file_reader);
	return (get_line);
}
