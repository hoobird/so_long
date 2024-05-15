/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_byebye.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:01:58 by hulim             #+#    #+#             */
/*   Updated: 2024/05/15 15:41:52 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	destroy(t_game *mlxstruct)
{
	mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgwall);
	mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgfloor);
	mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgexit);
	mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgcollectible);
	mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgplayer);
	freemap(mlxstruct->map);
	mlx_destroy_window(mlxstruct->mlx, mlxstruct->win);
	mlx_destroy_display(mlxstruct->mlx);
	free(mlxstruct->mlx);
	free(mlxstruct);
	exit(0);
}

int	printerror(void)
{
	ft_printf("Error\n");
	return (0);
}
