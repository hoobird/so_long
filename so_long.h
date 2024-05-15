/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:10:26 by hulim             #+#    #+#             */
/*   Updated: 2024/05/15 15:27:04 by hulim            ###   ########.fr       */
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

#ifndef ULONGMAX
# define ULONGMAX 4294967295
#endif

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

typedef struct s_floodhelper
{
	int		collectibles;
	int		exits;
} t_floodhelper;

// so_setup.c
void	setupmlx(t_game *mlxstruct, char **map);
void	getplayercollectwherabouts(t_game *mlxstruct);
void	whereaboutshelper(t_game *mlxstruct, int i, int j);

// so_floodfill.c
void	floodfillcheck(t_game *mlxstruct);
char	**duplicatemap(t_game *mlxstruct);
void	floodfill(char **dupmap, t_floodhelper *floodhelper, int x, int y);

// so_stringstuff.c
int		so_isspacee(char c);
char	*so_trimfilename(char *filename);
char	*so_trimnewline(char *line);
int		bercheck(char *file);
int		so_isspacee(char c);

// so_mapvalidate.c
char	**readandvalidatemap(char *file);
int		validatemap(char **map);
int		checkmaprect(char **map);
int		checkmapborder(char **map);
int		checkmapcontent(char **map);

// so_maphelper.c
int		mapheightcount(char *file);
int		check_symbol(char symbol, int *player, int *exit, int *collectible);
void	*freemap(char **map);
int		getmapheight(char **map);

// so_bindings.c
void	bindings(t_game *mlxstruct);
int		keybindings(int keycode, t_game *mlxstruct);

// so_display.c
void	displaymap(t_game *mlxstruct);
void	displaycheckssymbol(t_game *mlxstruct, int j, int i);
int		xoffset(t_game *mlxstruct);
int		yoffset(t_game *mlxstruct);

// so_display2.c
void	 drawimgpixelstoimg(t_game *mlxs, void *imgput, int x, int y);
void	setbpbd(t_game *mlxs, void *imgput, char **bp, char **bd);
void	putrgba(char *bufferdisplay, char *bufferput, int bdindex, int bpindex);

// so_moving.c
void move(t_game *mlxstruct, char dir);

// so_byebye.c
int destroy(t_game *mlxstruct);
int printerror(void);

// so_winning.c
void checkifwon(t_game *mlxstruct);

// so_long.c
int	repeat(t_game *mlxstruct);

#endif
