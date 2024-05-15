/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_bindings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:39:22 by hulim             #+#    #+#             */
/*   Updated: 2024/05/15 16:01:14 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	bindings(t_game *mlxstruct)
{
	mlx_hook(mlxstruct->win, 17, 0L, destroy, mlxstruct);
	mlx_hook(mlxstruct->win, 2, 1L << 0, keybindings, mlxstruct);
}

int	keybindings(int keycode, t_game *mlxstruct)
{
	if (keycode == 65307)
		destroy(mlxstruct);
	if (keycode == 119)
		move(mlxstruct, 'u');
	if (keycode == 115)
		move(mlxstruct, 'd');
	if (keycode == 97)
		move(mlxstruct, 'l');
	if (keycode == 100)
		move(mlxstruct, 'r');
	return (0);
}
