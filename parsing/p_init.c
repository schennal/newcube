/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:38:45 by aandom            #+#    #+#             */
/*   Updated: 2024/06/19 20:25:27 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	init_tmap(t_map *inputmap)
{
	inputmap->fd = 0;
	inputmap->line_count = 0;
	inputmap->path = NULL;
	inputmap->file = NULL;
	inputmap->height = 0;
	inputmap->width = 0;
	inputmap->end_idx = 0;
}

void	duplicate_parse(t_parse *parse)
{
	parse->num_lines = parse->ip_map.line_count;
	parse->text = parse->ip_map.file;
	parse->column = parse->ip_map.width;
	parse->row = parse->ip_map.height;
}

void	init_tparse(t_parse *parse)
{
	parse->north_wall = NULL;
	parse->south_wall = NULL;
	parse->west_wall = NULL;
	parse->east_wall = NULL;
	parse->map = NULL;
	parse->floor = 0;
	parse->ceiling = 0;
}
