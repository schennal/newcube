/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:46:35 by aandom            #+#    #+#             */
/*   Updated: 2024/06/19 20:04:20 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

static char	*substitute_tabs(char **line, char **new_line, int len, int j)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (++i < len)
	{
		if ((*line)[i] == '\t')
		{
			while (++k <= 4)
				(*new_line)[j++] = ' ';
			k = 0;
		}
		else
			(*new_line)[j++] = (*line)[i];
	}
	free(*line);
	return (*new_line);
}

static void	handle_tab(char **line, int i, int len, int tab_count)
{
	int		new_len;
	char	*new_line;

	len = ft_strlen(*line);
	while (++i < len)
		if ((*line)[i] == '\t')
			tab_count++;
	if (tab_count == 0)
		return ;
	new_len = len + (tab_count * 3);
	new_line = ft_calloc(new_len + 1, sizeof(char));
	*line = substitute_tabs(line, &new_line, len, 0);
}

static void	dup_map_file(int row, int column, int i, t_parse *parse)
{
	char	*line;

	line = get_next_line_3(parse->ip_map.fd);
	while (line != NULL)
	{
		handle_tab(&line, -1, 0, 0);
		if (ft_strchr(line, '\n') != 0)
			parse->ip_map.file[row] = ft_calloc(ft_strlen(line), sizeof(char));
		else
			parse->ip_map.file[row] = ft_calloc(ft_strlen(line) + 1,
					sizeof(char));
		if (!parse->ip_map.file[row])
		{
			print_err(NULL, "Couldn't allocate memory", 0);
			return (void_free_arr((void **)parse->ip_map.file));
		}
		while (line[i] != '\n' && line[i] != '\0')
			parse->ip_map.file[row][column++] = line[i++];
		parse->ip_map.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line_3(parse->ip_map.fd);
	}
	parse->ip_map.file[row] = NULL;
}

static int	get_line_num(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_err(path, strerror(errno), errno);
	else
	{
		line = get_next_line_3(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line_3(fd);
		}
		close(fd);
	}
	return (line_count);
}

void	parse_map(char *path, t_parse *parse)
{
	int		row;
	size_t	col;
	int		i;

	i = 0;
	row = 0;
	col = 0;
	parse->ip_map.line_count = get_line_num(path);
	parse->ip_map.path = path;
	if (parse->ip_map.line_count == 0)
		return ((void)(print_err(NULL, "EMPTY_MAP_FILE", 0)));
	parse->ip_map.file = ft_calloc(parse->ip_map.line_count + 1, sizeof(char *));
	if (!(parse->ip_map.file))
		return ((void)(print_err(NULL, "Couldn't allocate memory", 0)));
	parse->ip_map.fd = open(path, O_RDONLY);
	if (parse->ip_map.fd < 0)
		print_err(path, strerror(errno), 1);
	else
	{
		dup_map_file(row, col, i, parse);
		close(parse->ip_map.fd);
	}
}
