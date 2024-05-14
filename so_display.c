/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:51:14 by hulim             #+#    #+#             */
/*   Updated: 2024/05/14 21:56:05 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	displaymap(t_game *mlxstruct)
{
	int		i;
	int		j;
	void	*img;
	int		iconwidth;
	int		iconheight;

	mlxstruct->imgdisplay = mlx_new_image(mlxstruct->mlx, mlxstruct->mapwidth,
			mlxstruct->mapheight);
	i = 0;
	while (mlxstruct->map[i] != NULL)
	{
		j = 0;
		while (mlxstruct->map[i][j])
			displaycheckssymbol(mlxstruct, j++, i);
		i++;
	}
	drawimgpixelstoimg(mlxstruct, mlxstruct->imgplayer, mlxstruct->playerx
		* mlxstruct->imgsize + xoffset(mlxstruct), mlxstruct->playery
		* mlxstruct->imgsize + yoffset(mlxstruct));
	mlx_clear_window(mlxstruct->mlx, mlxstruct->win);
	mlx_put_image_to_window(mlxstruct->mlx, mlxstruct->win,
		mlxstruct->imgdisplay, 0, 0);
	mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgdisplay);
}

void	displaycheckssymbol(t_game *mlxstruct, int j, int i)
{
	drawimgpixelstoimg(mlxstruct, mlxstruct->imgfloor, j * mlxstruct->imgsize
		+ xoffset(mlxstruct), i * mlxstruct->imgsize + yoffset(mlxstruct));
	if (mlxstruct->map[i][j] == '1')
		drawimgpixelstoimg(mlxstruct, mlxstruct->imgwall, j * mlxstruct->imgsize
			+ xoffset(mlxstruct), i * mlxstruct->imgsize + yoffset(mlxstruct));
	if (mlxstruct->map[i][j] == 'E')
		drawimgpixelstoimg(mlxstruct, mlxstruct->imgexit, j * mlxstruct->imgsize
			+ xoffset(mlxstruct), i * mlxstruct->imgsize + yoffset(mlxstruct));
	if (mlxstruct->map[i][j] == 'C')
		drawimgpixelstoimg(mlxstruct, mlxstruct->imgcollectible, j
			* mlxstruct->imgsize + xoffset(mlxstruct), i * mlxstruct->imgsize
			+ yoffset(mlxstruct));
}

int	xoffset(t_game *mlxstruct)
{
	int	x;

	x = mlxstruct->playerx * mlxstruct->imgsize;
	return (mlxstruct->mapwidth / 2 - x);
}

int	yoffset(t_game *mlxstruct)
{
	int	y;

	y = mlxstruct->playery * mlxstruct->imgsize;
	return (mlxstruct->mapheight / 2 - y);
}
