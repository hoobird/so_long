/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:11:36 by hulim             #+#    #+#             */
/*   Updated: 2024/05/25 17:46:31 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	**map;
	t_game	*mlxstruct;

	if (argc != 2 || bercheck(so_trimfilename(argv[1])) == 0)
		return (printerror());
	map = readandvalidatemap(so_trimfilename(argv[1]));
	if (map == NULL)
		return (printerror());
	mlxstruct = malloc(sizeof(t_game));
	setupmlx(mlxstruct, map);
	floodfillcheck(mlxstruct);
	displaymap(mlxstruct);
	bindings(mlxstruct);
	mlx_loop_hook(mlxstruct->mlx, repeat, mlxstruct);
	mlx_loop(mlxstruct->mlx);
	return (0);
}

int	repeat(t_game *mlxstruct)
{
	displaymap(mlxstruct);
	checkifwon(mlxstruct);
	return (0);
}
