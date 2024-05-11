/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:10:26 by hulim             #+#    #+#             */
/*   Updated: 2024/05/11 22:50:26 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "ft_printf/ft_printf.h"
# include "ft_printf/libft/libft.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		mapwidth;
	int		mapheight;
	int		mapoffsetx;
	int		mapoffsety;
	int		playerx;
	int		playery;
	int		exitx;
	int		exity;
	int		playermoves;
	int		collectibles;
	int		collectiblesfound;
	int		imgsize;
	void	*imgwall;
	void	*imgfloor;
	void	*imgexit;
	void	*imgcollectible;
	void	*imgplayer;
	void	*imgdisplay;
}		t_game;

#endif
