/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:34:25 by schennal          #+#    #+#             */
/*   Updated: 2024/06/21 20:35:44 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

/*we are fist initialising the game environment.by caing the init_game.
then we enter a loop where horizontal and vetical ray casting are performed.
we also have specila function to avoid the fish_eye which is mainly caused due to the non-linear mapping
of rays.
we also make sure that the player is within the rnge of 0 tp 2*pi*/

int	init_buffer(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			data->buffer[i][j] = WHITE;
			j++;
		}
		i++;
	}
	return (0);
}

void	init_gun(t_data *data)
{
	int	i;
	int	x;
	int	y;
	int	start_x;

	i = 0;
	y = WIN_H - data->gun.t_height;
	start_x = (WIN_W - data->gun.t_width) / 2;
	while (y < WIN_H && i < data->gun.t_height)
	{
		x = 0;
		while (x < data->gun.t_width)
		{
			if ((y >= 0 && y < WIN_H) && (start_x + x >= 0 && start_x
					+ x < WIN_W))
			{
				data->buffer[y][start_x + x] = data->gun.addr[i
					* data->gun.t_width + x];
			}
			x++;
		}
		y++;
		i++;
	}
}

int	init_rays(t_data *data)
{
	data->ray.angle = data->player.angle + (FOV * PI / 180) / 2.0;
	if (data->ray.angle > 2 * PI)
		data->ray.angle -= 2 * PI;
	if (data->ray.angle < 0)
		data->ray.angle += 2 * PI;
	data->ray.x = data->player.x_pos;
	data->ray.y = data->player.y_pos;
	return (0);
}

void	init_game(t_data *data)
{
	init_rays(data);
	init_buffer(data);
	init_gun(data);
	init_minimap(data, data->parse->map, data->parse->column * 8,
		data->parse->row * 8);
}

// int	let_the_game_begin(t_data *data, t_ray *ray)
// {
// 	int	i;
// 	int	x_intercept;
// 	int	y_intercept;

// 	i = -1;
// 	init_game(data);
// 	while (++i < WIN_W)
// 	{
// 		h_raycast(ray, data->parse->map);
// 		x_intercept = ray->x_intercept;
// 		y_intercept = ray->y_intercept;
// 		v_raycast(ray, data->parse->map);
// 		shortest_ray(data, ray, x_intercept, y_intercept);
// 		fix_fish_eye(ray, data->player.angle);
// 		init_wall(ray, data, i);
// 		draw_ray(data, ray->x / 64 * 8, ray->y / 64 * 8, ray->intercepts);
// 		ray->angle -= data->angle_increment;
// 		if (data->player.angle > 2 * PI)
// 			data->player.angle -= 2 * PI;
// 		if (data->ray.angle < 0)
// 			data->ray.angle += 2 * PI;
// 	}
// 	draw_game(data);
// 	return (0);
// }

int	let_the_game_begin(t_data *data, t_ray *ray)
{
	int	i;
	int	x_intercept;
	int	y_intercept;

	i = -1;
	init_game(data);
	while (++i < WIN_W)
	{
		h_raycast(ray, data->parse->map);
		x_intercept = ray->x_intercept;
		y_intercept = ray->y_intercept;
		v_raycast(ray, data->parse->map);
		shortest_ray(data, ray, x_intercept, y_intercept);
		fix_fish_eye(ray, data->player.angle);
		init_wall(ray, data, i);
		draw_ray(data, ray->x / 64 * 8, ray->y / 64 * 8, ray->intercepts);
		ray->angle -= data->angle_increment;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		if (ray->angle < 0)
			ray->angle += 2 * PI;
	}
	draw_game(data);
	return (0);
}

