/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_display2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:03:43 by hulim             #+#    #+#             */
/*   Updated: 2024/05/17 00:17:42 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
bp : Buffer Put
bd : Buffer Display
*/
void	drawimgpixelstoimg(t_game *mlxs, void *imgput, int x, int y)
{
	int		i;
	int		j;
	char	*bp;
	char	*bd;

	setbpbd(mlxs, imgput, &bp, &bd);
	i = -1;
	while (++i < mlxs->imgsize)
	{
		j = -1;
		while (++j < mlxs->imgsize)
		{
			if ((unsigned int)bp[4 * (i * mlxs->imgsize + j) + 3] != ULONGMAX)
			{
				if (y + i >= mlxs->mapheight || y + i < 0
					|| x + j >= mlxs->mapwidth || x + j < 0)
					continue ;
				putrgba(bd, bp, 4 * ((y + i) * mlxs->mapwidth + (x + j)),
					4 * (i * mlxs->imgsize + j));
			}
		}
	}
}

void	setbpbd(t_game *mlxs, void *imgput, char **bp, char **bd)
{
	int	temp;

	*bp = mlx_get_data_addr(imgput, &temp, &temp, &temp);
	*bd = mlx_get_data_addr(mlxs->imgdisplay, &temp, &temp, &temp);
}

void	putrgba(char *bufferdisplay, char *bufferput, int bdindex, int bpindex)
{
	bufferdisplay[bdindex] = bufferput[bpindex];
	bufferdisplay[bdindex + 1] = bufferput[bpindex + 1];
	bufferdisplay[bdindex + 2] = bufferput[bpindex + 2];
	bufferdisplay[bdindex + 3] = bufferput[bpindex + 3];
}
