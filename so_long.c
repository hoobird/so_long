/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:11:36 by hulim             #+#    #+#             */
/*   Updated: 2024/05/12 17:44:34 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	isspacee(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char *trimfilename(char *filename)
{
	int i = 0;
	int j = ft_strlen(filename) - 1;
	
	while (isspacee(filename[i]))
		i++;
	
	while (j >= i && isspacee(filename[j]))
	{
		filename[j] = '\0';
		j--;
	}
	return (filename + i);
}

char	*trimnewline(char *line)
{
	char	*new;
	int		i;
	int		j;
	
	i = 0;
	while (line[i])
		i++;
	i--;
	while (i >= 0 && isspacee(line[i]))
		i--;
	if (i == -1)
	{
		free(line);
		return (NULL);
	}
	new = ft_calloc(i + 2, sizeof(char));
	j = 0;
	while (j < i + 1)
	{
		new[j] = line[j];
		j++;
	}
	free(line);
	return (new);		
}

int	bercheck(char *file)
{
	int		i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 4] != '.' || file[i - 3] != 'b' || file[i - 2] != 'e' || file[i - 1] != 'r')
		return (0);
	return (1);
}

int	mapheightcount(char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		line = trimnewline(line);
		if (line != NULL)
			i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	checkmaprect(char **map)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	len = ft_strlen(map[0]);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j != len)
			return (0);
		i++;
	}
	return (1);
}

int	checkmapborder(char **map)
{
	int		i;
	int		j;
	int		height;

	height = 0;
	while (map[height] != NULL)
		height++;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == 0 || i == height || j == 0 || j == ft_strlen(map[i]) - 1)
			{
				if (map[i][j] != '1')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int check_symbol(char symbol, int *player, int *exit, int *collectible)
{
	if (symbol == 'P')
		(*player)++;
	else if (symbol == 'E')
		(*exit)++;
	else if (symbol == 'C')
		(*collectible)++;
	else if (symbol != '0' && symbol != '1')
		return (0);
	return (1);
}

int	checkmapcontent(char **map)
{
	int		i;
	int		j;
	int		player;
	int		exit;
	int		collectible;

	player = 0;
	exit = 0;
	collectible = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_symbol(map[i][j], &player, &exit, &collectible) == 0)
				return (0);
			j++;
		}
		i++;
	}
	if (player != 1 || exit != 1 || collectible < 1)
		return (0);
	return (1);	
}

int	validatemap(char **map)
{
	if (checkmaprect(map) == 0 || checkmapborder(map) == 0 || checkmapcontent(map) == 0)
		return (0);
	return (1); 
}

void	printmap(t_game *mlxstruct)
{
	int		i;
	int		j;

	i = 0;
	while (mlxstruct->map[i] != NULL)
	{
		j = 0;
		while (mlxstruct->map[i][j])
		{
			if (i == mlxstruct->playery && j == mlxstruct->playerx)
				ft_printf("P");
			else
				ft_printf("%c", mlxstruct->map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	freemap(char **map)
{
	int		i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**readandvalidatemap(char *file)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	map = ft_calloc(mapheightcount(file) + 1, sizeof(char *));
	line = get_next_line(fd);
	while (line)
	{
		line = trimnewline(line);
		if (line != NULL)
			map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	if (validatemap(map) == 0)
	{
		freemap(map);
		return (NULL);
	}
	return (map);
}

int	printerror()
{
	ft_printf("Error\n");
	return (0);
}

int	destroy(t_game *mlxstruct)
{
	mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgwall);
	mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgfloor);
	mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgexit);
	mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgcollectible);
	mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgplayer);
	// mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgdisplay);
	freemap(mlxstruct->map);
	mlx_destroy_window(mlxstruct->mlx, mlxstruct->win);
	free(mlxstruct);
	exit(0);
}

void	move(t_game *mlxstruct, char dir)
{
	int		newx;
	int		newy;

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
	printmap(mlxstruct);
	ft_printf("Player moves: %d\n", mlxstruct->playermoves);
}

void	checkifwon(t_game *mlxstruct)
{
	if (mlxstruct->collectiblesfound == mlxstruct->collectibles && mlxstruct->playerx == mlxstruct->exitx && mlxstruct->playery == mlxstruct->exity)
	{
		ft_printf("You won!\n");
		destroy(mlxstruct);
	}
}

int	keybindings(int keycode, t_game *mlxstruct)
{
	ft_printf("Key pressed: %d\n", keycode);
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
}

void	bindings(t_game *mlxstruct)
{
	mlx_hook(mlxstruct->win, 17, 0L, destroy, mlxstruct);
	mlx_hook(mlxstruct->win, 2, 1L<<0, keybindings, mlxstruct);
}

int	getmapheight(char **map)
{
	int		i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

void	getplayercollectwherabouts(t_game *mlxstruct)
{
	int		i;
	int		j;

	i = 0;
	mlxstruct->collectibles = 0;
	while (mlxstruct->map[i] != NULL)
	{
		j = 0;
		while (mlxstruct->map[i][j])
		{
			if (mlxstruct->map[i][j] == 'P')
			{
				mlxstruct->playerx = j;
				mlxstruct->playery = i;
				mlxstruct->map[i][j] = '0';
			}
			if (mlxstruct->map[i][j] == 'C')
				mlxstruct->collectibles++;
			if (mlxstruct->map[i][j] == 'E')
			{
				mlxstruct->exitx = j;
				mlxstruct->exity = i;
			}
			j++;
		}
		i++;
	}
}

void	setupmlx(t_game *mlxstruct, char **map)
{
	mlxstruct->mlx = mlx_init();
	mlxstruct->imgwall = mlx_xpm_file_to_image(mlxstruct->mlx, "./wall.xpm", &mlxstruct->imgsize, &mlxstruct->imgsize);
	mlxstruct->imgfloor = mlx_xpm_file_to_image(mlxstruct->mlx, "./ground.xpm", &mlxstruct->imgsize, &mlxstruct->imgsize);
	mlxstruct->imgexit = mlx_xpm_file_to_image(mlxstruct->mlx, "./eve.xpm", &mlxstruct->imgsize, &mlxstruct->imgsize);
	mlxstruct->imgcollectible = mlx_xpm_file_to_image(mlxstruct->mlx, "./sapling.xpm", &mlxstruct->imgsize, &mlxstruct->imgsize);
	mlxstruct->imgplayer = mlx_xpm_file_to_image(mlxstruct->mlx, "./walle.xpm", &mlxstruct->imgsize, &mlxstruct->imgsize);
	mlxstruct->map = map;
	getplayercollectwherabouts(mlxstruct);
	mlxstruct->playermoves = 0;
	mlxstruct->collectiblesfound = 0;
	mlxstruct->mapwidth = 1920;
	mlxstruct->mapheight = 1040;
	mlxstruct->win = mlx_new_window(mlxstruct->mlx, mlxstruct->mapwidth, mlxstruct->mapheight, "so_long");
}

void	drawimgpixelstoimg(t_game *mlxstruct, void *imgput, int x, int y)
{
	int		i;
	int		j;
	char 	*bufferput;
	char	*bufferdisplay;
	int		temp;
	int 	srcPixel;
	int 	destPixel;

	if (x < 0 || y < 0 || x >= mlxstruct->mapwidth || y >= mlxstruct->mapheight)
		return ;

	bufferput = mlx_get_data_addr(imgput, &temp, &temp, &temp);
	bufferdisplay = mlx_get_data_addr(mlxstruct->imgdisplay, &temp, &temp, &temp);
	i = 0;
	while (i < mlxstruct->imgsize)
	{
		j = 0;
		while (j < mlxstruct->imgsize)
		{
			srcPixel = (i * mlxstruct->imgsize * 4) + (j * 4);
			if ((unsigned int) bufferput[srcPixel + 3] != 4294967295)
			{
				destPixel = ((y + i) * mlxstruct->mapwidth * 4) + ((x + j) * 4);
				bufferdisplay[destPixel] = bufferput[srcPixel];
				bufferdisplay[destPixel + 1] = bufferput[srcPixel + 1] ;
				bufferdisplay[destPixel + 2] = bufferput[srcPixel + 2] ;
				bufferdisplay[destPixel + 3] = bufferput[srcPixel + 3] ;
			}
			j++;
		}
		i++;
	}
}

int	positify(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

int	xoffset(t_game *mlxstruct)
{
	int		x;

	x = mlxstruct->playerx * mlxstruct->imgsize;
	return (mlxstruct->mapwidth / 2 - x);
}

int	yoffset(t_game *mlxstruct)
{
	int		y;

	y = mlxstruct->playery * mlxstruct->imgsize;
	return (mlxstruct->mapheight / 2 - y);
}

void	displaymap(t_game *mlxstruct)
{
	int		i;
	int		j;
	void	*img;
	int		iconwidth;
	int		iconheight;

	mlxstruct->imgdisplay = mlx_new_image(mlxstruct->mlx, mlxstruct->mapwidth, mlxstruct->mapheight);
	i = 0;
	while (mlxstruct->map[i] != NULL)
	{
		j = 0;
		while (mlxstruct->map[i][j])
		{
			drawimgpixelstoimg(mlxstruct, mlxstruct->imgfloor, j * mlxstruct->imgsize + xoffset(mlxstruct), i * mlxstruct->imgsize + yoffset(mlxstruct));
			if (mlxstruct->map[i][j] == '1')
				drawimgpixelstoimg(mlxstruct, mlxstruct->imgwall, j * mlxstruct->imgsize+ xoffset(mlxstruct), i * mlxstruct->imgsize+ yoffset(mlxstruct));
			if (mlxstruct->map[i][j] == 'E')
				drawimgpixelstoimg(mlxstruct, mlxstruct->imgexit, j * mlxstruct->imgsize+ xoffset(mlxstruct), i * mlxstruct->imgsize+ yoffset(mlxstruct));
			if (mlxstruct->map[i][j] == 'C')
				drawimgpixelstoimg(mlxstruct, mlxstruct->imgcollectible, j * mlxstruct->imgsize+ xoffset(mlxstruct), i * mlxstruct->imgsize+ yoffset(mlxstruct));
			j++;
		}
		i++;
	}
	drawimgpixelstoimg(mlxstruct, mlxstruct->imgplayer, mlxstruct->playerx * mlxstruct->imgsize+ xoffset(mlxstruct), mlxstruct->playery * mlxstruct->imgsize+ yoffset(mlxstruct));
	mlx_clear_window(mlxstruct->mlx, mlxstruct->win);
	mlx_put_image_to_window(mlxstruct->mlx, mlxstruct->win, mlxstruct->imgdisplay, 0, 0);
	mlx_destroy_image(mlxstruct->mlx, mlxstruct->imgdisplay);
}
int repeat(t_game *mlxstruct)
{
	displaymap(mlxstruct);
	checkifwon(mlxstruct);
	return (0);
}

int	main(int argc, char **argv)
{
	char	**map;
	t_game	*mlxstruct;
	void	*img;

	if (argc != 2 || bercheck(trimfilename(argv[1])) == 0)
		return (printerror());
	map = readandvalidatemap(trimfilename(argv[1]));
	if (map == NULL)
		return (printerror());
	mlxstruct = malloc(sizeof(t_game));
	setupmlx(mlxstruct, map);
	printmap(mlxstruct);
	displaymap(mlxstruct);
	bindings(mlxstruct);
	mlx_loop_hook(mlxstruct->mlx, repeat, mlxstruct);
	mlx_loop(mlxstruct->mlx);
	return (0);
}


