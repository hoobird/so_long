/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_display2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:03:43 by hulim             #+#    #+#             */
/*   Updated: 2024/05/14 22:44:53 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	drawimgpixelstoimg(t_game *mlxs, void *imgput, int x, int y)
{
	int		i;
	int		j;
	char	*bufferput;
	char	*bufferdisplay;
	int		temp;

	if (x < 0 || y < 0 || x >= mlxs->mapwidth || y >= mlxs->mapheight)
		return ;
	bufferput = mlx_get_data_addr(imgput, &temp, &temp, &temp);
	bufferdisplay = mlx_get_data_addr(mlxs->imgdisplay, &temp, &temp, &temp);
	i = 0;
	while (i < mlxs->imgsize)
	{
		j = 0;
		while (j < mlxs->imgsize)
		{
			if ((unsigned int)bufferput[(i * mlxs->imgsize * 4) + (j * 4) + 3]
				!= 4294967295)
			{
				if ((y + i) * mlxs->mapwidth * 4 + ((x + j) * 4) < 0
					|| (y + i) * mlxs->mapwidth * 4 + ((x + j) * 4)
					>= mlxs->mapwidth * mlxs->mapheight * 4)
					break ;
				bufferdisplay[(y + i) * mlxs->mapwidth * 4 + ((x + j) * 4)]
					= bufferput[(i * mlxs->imgsize * 4) + (j * 4)];
				bufferdisplay[(y + i) * mlxs->mapwidth * 4 + ((x + j) * 4) + 1]
					= bufferput[(i * mlxs->imgsize * 4) + (j * 4) + 1];
				bufferdisplay[(y + i) * mlxs->mapwidth * 4 + ((x + j) * 4) + 2]
					= bufferput[(i * mlxs->imgsize * 4) + (j * 4) + 2];
				bufferdisplay[(y + i) * mlxs->mapwidth * 4 + ((x + j) * 4) + 3]
					= bufferput[(i * mlxs->imgsize * 4) + (j * 4) + 3];
			}
			j++;
		}
		i++;
	}
}
