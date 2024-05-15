/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_floodfill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:45:59 by hulim             #+#    #+#             */
/*   Updated: 2024/05/15 16:11:27 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	floodfillcheck(t_game *mlxstruct)
{
	char			**dupmap;
	t_floodhelper	*floodhelper;

	dupmap = duplicatemap(mlxstruct);
	floodhelper = malloc(sizeof(t_floodhelper));
	floodhelper->collectibles = 0;
	floodhelper->exits = 0;
	floodfill(dupmap, floodhelper, mlxstruct->playerx, mlxstruct->playery);
	freemap(dupmap);
	if (floodhelper->collectibles != mlxstruct->collectibles
		|| floodhelper->exits != 1)
	{
		free(floodhelper);
		ft_printf("Error\n");
		destroy(mlxstruct);
	}
	free(floodhelper);
}

char	**duplicatemap(t_game *mlxstruct)
{
	int		i;
	int		j;
	char	**dupmap;

	i = 0;
	dupmap = ft_calloc(getmapheight(mlxstruct->map) + 1, sizeof(char *));
	while (i < getmapheight(mlxstruct->map))
	{
		dupmap[i] = ft_calloc((int)ft_strlen(mlxstruct->map[i]) + 1,
				sizeof(char));
		j = 0;
		while (j < (int)ft_strlen(mlxstruct->map[i]))
		{
			dupmap[i][j] = mlxstruct->map[i][j];
			j++;
		}
		i++;
	}
	return (dupmap);
}

void	floodfill(char **dupmap, t_floodhelper *floodhelper, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)ft_strlen(dupmap[y])
		|| y >= getmapheight(dupmap))
		return ;
	if (dupmap[y][x] == '1')
		return ;
	if (dupmap[y][x] == 'C')
		floodhelper->collectibles++;
	if (dupmap[y][x] == 'E')
		floodhelper->exits++;
	dupmap[y][x] = '1';
	if (y > 0)
		floodfill(dupmap, floodhelper, x, y - 1);
	if (y < getmapheight(dupmap) - 1)
		floodfill(dupmap, floodhelper, x, y + 1);
	if (x > 0)
		floodfill(dupmap, floodhelper, x - 1, y);
	if (x < (int)ft_strlen(dupmap[y]) - 1)
		floodfill(dupmap, floodhelper, x + 1, y);
}
