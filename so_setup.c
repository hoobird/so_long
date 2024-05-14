/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:42:31 by hulim             #+#    #+#             */
/*   Updated: 2024/05/14 20:44:50 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	setupmlx(t_game *mlxstruct, char **map)
{
	mlxstruct->mlx = mlx_init();
	mlxstruct->imgwall = mlx_xpm_file_to_image(mlxstruct->mlx, "./wall.xpm",
			&mlxstruct->imgsize, &mlxstruct->imgsize);
	mlxstruct->imgfloor = mlx_xpm_file_to_image(mlxstruct->mlx, "./ground.xpm",
			&mlxstruct->imgsize, &mlxstruct->imgsize);
	mlxstruct->imgexit = mlx_xpm_file_to_image(mlxstruct->mlx, "./eve.xpm",
			&mlxstruct->imgsize, &mlxstruct->imgsize);
	mlxstruct->imgcollectible = mlx_xpm_file_to_image(mlxstruct->mlx,
			"./sapling.xpm", &mlxstruct->imgsize, &mlxstruct->imgsize);
	mlxstruct->imgplayer = mlx_xpm_file_to_image(mlxstruct->mlx, "./walle.xpm",
			&mlxstruct->imgsize, &mlxstruct->imgsize);
	mlxstruct->map = map;
	getplayercollectwherabouts(mlxstruct);
	mlxstruct->playermoves = 0;
	mlxstruct->collectiblesfound = 0;
	mlxstruct->mapwidth = 1920;
	mlxstruct->mapheight = 1040;
	mlxstruct->win = mlx_new_window(mlxstruct->mlx, mlxstruct->mapwidth,
			mlxstruct->mapheight, "so_long");
}

void	getplayercollectwherabouts(t_game *mlxstruct)
{
	int	i;
	int	j;

	i = 0;
	mlxstruct->collectibles = 0;
	while (mlxstruct->map[i] != NULL)
	{
		j = 0;
		while (mlxstruct->map[i][j])
		{
			whereaboutshelper(mlxstruct, i, j);
			j++;
		}
		i++;
	}
}

void	whereaboutshelper(t_game *mlxstruct, int i, int j)
{
	if (mlxstruct->map[i][j] == 'P')
	{
		mlxstruct->playerx = j;
		mlxstruct->playery = i;
		mlxstruct->map[i][j] = '0';
	}
	if (mlxstruct->map[i][j] == 'C')
		mlxstruct->collectibles++;
	if (mlxstruct->map[i][j] == 'E')
	{
		mlxstruct->exitx = j;
		mlxstruct->exity = i;
	}
}
