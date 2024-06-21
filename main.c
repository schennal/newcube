/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:23:39 by schennal          #+#    #+#             */
/*   Updated: 2024/06/21 18:14:28 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_parse	parse;

	if (ac != 2)
	{
		printf("Usage: cube3d ./maps/map1.cub\n");
		printf("Wrong arguments");
		return (EXIT_FAILURE);
	}
	if (!parser(&parse, av[1]))
		return (EXIT_FAILURE);
	data.parse = &parse;
	init(&data);
	let_the_game_begin(&data, &data.ray);
	setup_hooks(&data);
	free_memory(&parse, &data);
	return (0);
}

int	init(t_data *data)
{
	init_data(data);
	init_player(data);
	data->player.delta_x = cos(data->player.angle) * STEP_SIZE;
	data->player.delta_y = -sin(data->player.angle) * STEP_SIZE;
	init_keys(data);
	init_window(data);
	init_texture(data->parse, data);
	return (0);
}
