/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:26:36 by aandom            #+#    #+#             */
/*   Updated: 2024/06/21 16:23:41 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int	check_front(char **map, int j, int i)
{
	while (i >= 0)
	{
		if (map[j][i] == '1')
			return (1);
		i--;
	}
	return (0);
}

int	print_err(char *info, char *str, int code)
{
	ft_putstr_fd("cub3D: Error", 2);
	if (info)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(info, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", 2);
	return (code);
}

void	void_free_arr(void **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

int	print_err_val(int detail, char *str, int code)
{
	ft_putstr_fd("cub3D: Error: ", 2);
	ft_putnbr_fd(detail, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (code);
}

void	free_parser(t_parse *parse)
{
	free_double_array(&parse->ip_map.file);
	if (parse->map != NULL)
		free_double_array(&parse->map);
	if (parse->north_wall != NULL)
		free(parse->north_wall);
	if (parse->south_wall != NULL)
		free(parse->south_wall);
	if (parse->west_wall != NULL)
		free(parse->west_wall);
	if (parse->east_wall != NULL)
		free(parse->east_wall);
	if (parse->ceiling != NULL)
		free(parse->ceiling);
	if (parse->floor != NULL)
		free(parse->floor);

	// Set pointers to NULL after freeing
    parse->north_wall = NULL;
    parse->south_wall = NULL;
    parse->west_wall = NULL;
    parse->east_wall = NULL;
}
