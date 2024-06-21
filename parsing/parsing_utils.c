/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:06:24 by Degef             #+#    #+#             */
/*   Updated: 2024/06/21 16:38:12 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	free_double_array(char ***str)
{
	int	i;

	i = -1;
	while ((*str)[++i])
		free((*str)[i]);
	free(*str);
	*str = NULL;
}

void	free_double_array2(unsigned int ***str)
{
	int	i;

	i = -1;
	while ((*str)[++i])
		free((*str)[i]);
	free(*str);
}
