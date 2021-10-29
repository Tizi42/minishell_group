/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_n_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 00:32:30 by jkromer           #+#    #+#             */
/*   Updated: 2021/06/22 11:33:02 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strmerge_gnl(char *tmp, const char *buffer)
{
	char	*join;
	size_t	tmp_len;
	int		i;

	if (tmp)
		tmp_len = ft_strlen(tmp);
	else
		tmp_len = 0;
	join = malloc(sizeof(char) * (tmp_len + ft_strlen(buffer) + 1));
	if (!join)
		return (NULL);
	if (tmp)
	{
		i = -1;
		while (tmp[++i])
			join[i] = tmp[i];
	}
	i = -1;
	while (buffer[++i])
		join[tmp_len + i] = buffer[i];
	join[tmp_len + i] = 0;
	free(tmp);
	return (join);
}

static int	clean_up(char *tmp, char **line)
{
	free(tmp);
	if (line)
		*line = NULL;
	return (-1);
}

static char	*get_newline(char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
			return (ft_strndup(tmp, i));
		i++;
	}
	return (ft_strdup(tmp));
}

static int	update_tmp(char *tmp)
{
	int		i;
	char	*sub;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			sub = ft_strdup(tmp + i + 1);
			if (!sub)
				return (-1);
			ft_strcpy(tmp, sub);
			free(sub);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

int	get_n_line(int fd, char **line)
{
	static char	*tmp[256];
	char		buffer[BUFFER_SIZE + 1];
	int			n;
	int			ret;

	if (fd < 0 || fd > 255 || BUFFER_SIZE < 1 || !line)
		return (clean_up(tmp[fd], line));
	n = 1;
	buffer[0] = 0;
	while (n && !ft_contains(buffer, '\n'))
	{
		if (fill_buffer(fd, buffer, &n) == -1)
			return (clean_up(tmp[fd], line));
		tmp[fd] = ft_strmerge_gnl(tmp[fd], buffer);
		if (!tmp[fd])
			return (clean_up(tmp[fd], line));
	}
	*line = get_newline(tmp[fd]);
	ret = update_tmp(tmp[fd]);
	if (!*line || ret == -1)
		return (clean_up(tmp[fd], line));
	if (ret)
		return (1);
	tmp[fd] = NULL;
	return (0);
}
