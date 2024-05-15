/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_winning.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:05:09 by hulim             #+#    #+#             */
/*   Updated: 2024/05/15 15:31:22 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	checkifwon(t_game *mlxstruct)
{
	if (mlxstruct->collectiblesfound == mlxstruct->collectibles
		&& mlxstruct->playerx == mlxstruct->exitx
		&& mlxstruct->playery == mlxstruct->exity)
	{
		ft_printf("You won!\n");
		destroy(mlxstruct);
	}
}
