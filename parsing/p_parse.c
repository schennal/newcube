/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:18:22 by aandom            #+#    #+#             */
/*   Updated: 2024/06/21 16:41:11 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

static bool	is_cub(char *file_path)
{
	size_t	len;

	len = ft_strlen(file_path);
	if ((file_path[len - 3] != 'c' || file_path[len - 2] != 'u' || file_path[len
			- 1] != 'b' || file_path[len - 4] != '.'))
		return (false);
	return (true);
}

static bool	is_xmp(char *file_path)
{
	size_t	len;

	len = ft_strlen(file_path);
	if ((file_path[len - 3] != 'x' || file_path[len - 2] != 'p' || file_path[len
			- 1] != 'm' || file_path[len - 4] != '.'))
		return (false);
	return (true);
}

int	map_check(char *file_path, bool cub)
{
	int	fd;

	fd = open(file_path, O_DIRECTORY);
	if (fd >= 0)
		return (print_err(file_path, "is Directory", 1));
	close(fd);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (print_err(file_path, strerror(errno), 1));
	close(fd);
	if (cub && !is_cub(file_path))
		return (print_err(file_path, "not a .cub file", 1));
	if (!cub && !is_xmp(file_path))
		return (print_err(file_path, "not a .xmp file", 1));
	return (0);
}

int	parser(t_parse *parse, char *file_path)
{
	if (map_check(file_path, true) == 1)
		return (SUCCESS);
	parse->pdir = '\0';
	init_tmap(&parse->ip_map);
	parse_map(file_path, parse);
	if (parse->ip_map.file == NULL)
		return (SUCCESS);
	init_tparse(parse);
	if (get_map(parse, parse->ip_map.file) == 1)
		return (free_double_array(&parse->ip_map.file), 0);
	if (check_map_ifvalid(parse, parse->map) == FAILURE)
		return (free_parser(parse), 0);
	if (check_texture(parse) == FAILURE)
		return (free_parser(parse), 0);
	duplicate_parse(parse);
	return (1);
}
