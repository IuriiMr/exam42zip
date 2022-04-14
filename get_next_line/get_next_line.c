/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarushe <imarushe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:06:44 by imarushe          #+#    #+#             */
/*   Updated: 2022/04/06 15:37:39 by imarushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	ft_isin(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i =0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *temp, char *buffer)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(temp) + ft_strlen(buffer) + 1));
	if (!result)
		return (NULL);
	while (temp[i])
	{
		result[i] = temp[i];
		i++;
	}
	while (buffer[j])
	{
		result[i + j] = buffer[j];
		j++;
	}
	result[i + j] = '\0';
	free(temp);
	return(result);
}

char	*ft_read(int fd, char *temp)
{
	int		bread;
	char	*buffer;

	bread = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (ft_isin(temp, '\n') && bread)
	{
		bread = read(fd, buffer, BUFFER_SIZE);
		if (bread < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bread] = '\0';
		temp = ft_strjoin(temp, buffer);
	}
	free(buffer);
	return (temp);
}

char *ft_get_line(char *temp)
{
	int	i;
	char *line;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] && temp[i] == '\n')
		i++;
	line  = malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] && temp[i] == '\n')
	{
		line[i] = temp[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char *ft_next(char *temp, char *line)
{
	int	i;
	int	j;
	char	*result;

	j = 0;
	if (!temp[0])
	{
		free(temp);
		return (NULL);
	}
	result = malloc(sizeof(char) * (ft_strlen(temp) - ft_strlen(line) + 1));
	if (!result)
		return(NULL);
	i = ft_strlen(line);
	while (temp[i + j])
	{
		result[j] = temp[i + j];
		j++;
	}
	result[j] = '\0';
	free(temp);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;

	if (!temp)
	{
		temp = malloc(sizeof(char));
		if (!temp)
			return (NULL);
		temp[0] = '\0';
	}
	temp = ft_read(fd, temp);
	line = ft_get_line(temp);
	temp = ft_next(temp, line);
	return (line);
}

int	main(void)
{
	int	fd;
	char *str;

	fd = open("test.txt", O_RDONLY);
	str = get_next_line(fd);
	while(str[0])
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	return (0);
}c
