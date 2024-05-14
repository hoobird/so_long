/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_moving.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:59:43 by hulim             #+#    #+#             */
/*   Updated: 2024/05/14 22:00:09 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	move(t_game *mlxstruct, char dir)
{
	int	newx;
	int	newy;

	newx = mlxstruct->playerx;
	newy = mlxstruct->playery;
	if (dir == 'u')
		newy--;
	if (dir == 'd')
		newy++;
	if (dir == 'l')
		newx--;
	if (dir == 'r')
		newx++;
	if (mlxstruct->map[newy][newx] == '1')
		return ;
	mlxstruct->playermoves++;
	if (mlxstruct->map[newy][newx] == 'C')
	{
		mlxstruct->collectiblesfound++;
		mlxstruct->map[newy][newx] = '0';
	}
	mlxstruct->playerx = newx;
	mlxstruct->playery = newy;
	ft_printf("Player moves: %d\n", mlxstruct->playermoves);
}
