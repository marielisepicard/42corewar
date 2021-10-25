/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:26:22 by agelloz           #+#    #+#             */
/*   Updated: 2020/02/13 17:57:43 by agelloz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	read_file(t_file *file)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;
	char	*tmp_curr;

	while ((ret = read(file->fd, buf, BUFF_SIZE)) > 0)
	{
		if (ret == BUFF_SIZE && buf[0] == '\0')
			return (FAILURE);
		buf[ret] = '\0';
		tmp_curr = file->curr;
		if ((tmp = ft_strchr(buf, '\n')))
		{
			file->state = 1;
			file->rest = ft_strdup(tmp + 1);
			buf[tmp - buf + 1] = '\0';
			file->curr = ft_strjoin(file->curr, buf);
			ft_strdel(&tmp_curr);
			return (SUCCESS);
		}
		file->curr = ft_strjoin(file->curr, buf);
		ft_strdel(&tmp_curr);
	}
	(file->curr && file->curr[0] != '\0') ? file->state = 1 : TRUE;
	return ((ret == -1) ? FAILURE : file->state);
}

static void	fill_line(t_file *file)
{
	char	*tmp;
	char	*tmp_rest;

	file->state = 0;
	if (file->rest)
	{
		if ((!(tmp = ft_strchr(file->rest, '\n'))) || (tmp && !*(tmp + 1)))
		{
			file->curr = ft_strdup(file->rest);
			if (tmp && !*(tmp + 1))
				file->state = 1;
			ft_strdel(&(file->rest));
		}
		else
		{
			file->curr = ft_strsub(file->rest, 0, tmp - file->rest + 1);
			tmp_rest = file->rest;
			file->rest = ft_strdup(tmp + 1);
			ft_strdel(&tmp_rest);
			file->state = 1;
		}
	}
}

int			get_next_line(const int fd, char **line)
{
	static t_file	file;

	if (fd >= 0 && line != NULL)
	{
		file.fd = fd;
		fill_line(&file);
		file.fd = fd;
		if (file.state != 1 && read_file(&file) == FAILURE)
			return (FAILURE);
		if (file.curr != NULL)
		{
			*line = ft_strdup(file.curr);
			ft_strdel(&file.curr);
		}
		return ((*line == NULL && file.state != 0) ? FAILURE : file.state);
	}
	else if (fd != CLEANUP)
		return (FAILURE);
	ft_strdel(&file.rest);
	ft_strdel(&file.curr);
	return (SUCCESS);
}
