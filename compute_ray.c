/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:17:12 by schennal          #+#    #+#             */
/*   Updated: 2024/06/21 16:57:20 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int	compute_h_wall_interception(t_ray *ray, char **map, double x_offset,
		double y_offset)
{
	int	num;

	num = 0;
	while (++num < 30)
	{
		if (ray->angle > 0 && ray->angle < PI)
			ray->y_intercept -= 0.0001;
		if (ray->angle > PI && ray->angle < 2 * PI)
			ray->y_intercept += 0.0001;
		if (is_wall(ray, ray->x_intercept, ray->y_intercept, map))
		{
			ray->h_wall_hit_flag = 1;
			ray->h_distance = pythagoras(ray, ray->x_intercept,
					ray->y_intercept);
			break ;
		}
		else
		{
			ray->x_intercept += x_offset;
			ray->y_intercept += y_offset;
		}
	}
	return (0);
}

int	h_raycast(t_ray *ray, char **map)
{
	double	tan1;
	double	x_offset;
	double	y_offset;

	tan1 = 1.0 / tan(ray->angle);
	x_offset = 0.0;
	y_offset = 0.0;
	ray->h_distance = 100000;
	if (sin(ray->angle) > 0)
	{
		ray->y_intercept = (((int)ray->y >> 6) << 6) - 0.0001;
		ray->x_intercept = ray->x + (ray->y - ray->y_intercept) * tan1;
		y_offset = -CUBE_SIZE;
		x_offset = CUBE_SIZE * tan1;
	}
	else if (sin(ray->angle) < 0)
	{
		ray->y_intercept = (((int)ray->y >> 6) << 6) + CUBE_SIZE;
		ray->x_intercept = ray->x + (ray->y - ray->y_intercept) * tan1;
		y_offset = CUBE_SIZE;
		x_offset = -CUBE_SIZE * tan1;
	}
	compute_h_wall_interception(ray, map, x_offset, y_offset);
	return (0);
}

int	compute_v_wall_interception(t_ray *ray, char **map, double x_offset,
		double y_offset)
{
	int	num;

	num = -1;
	while (++num < 30)
	{
		if (cos(ray->angle) > 0.0001)
			ray->x_intercept += 0.001;
		else if (cos(ray->angle) < -0.0001)
			ray->x_intercept -= 0.001;
		if (is_wall(ray, ray->x_intercept, ray->y_intercept, map))
		{
			ray->v_wall_hit_flag = 1;
			ray->v_distance = pythagoras(ray, ray->x_intercept,
					ray->y_intercept);
			break ;
		}
		else
		{
			ray->x_intercept += x_offset;
			ray->y_intercept += y_offset;
		}
	}
	return (0);
}

int	v_raycast(t_ray *ray, char **map)
{
	double	tan1;
	double	x_offset;
	double	y_offset;

	ray->v_distance = 100000;
	tan1 = tan(ray->angle);
	x_offset = 0.0;
	y_offset = 0.0;
	if (cos(ray->angle) > 0.001)
	{
		ray->x_intercept = (((int)ray->x >> 6) << 6) + CUBE_SIZE;
		ray->y_intercept = (ray->x - ray->x_intercept) * tan1 + ray->y;
		x_offset = CUBE_SIZE;
		y_offset = -CUBE_SIZE * tan1;
	}
	else if (cos(ray->angle) < -0.001)
	{
		ray->x_intercept = (((int)ray->x >> 6) << 6) - 0.001;
		ray->y_intercept = (ray->x - ray->x_intercept) * tan1 + ray->y;
		x_offset = -CUBE_SIZE;
		y_offset = CUBE_SIZE * tan1;
	}
	compute_v_wall_interception(ray, map, x_offset, y_offset);
	return (0);
}
