/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:11:36 by hulim             #+#    #+#             */
/*   Updated: 2024/05/11 03:33:37 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	displaymap(t_game *mlxstruct);

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
		ft_printf("linelen: %d\n", ft_strlen(line));
		line = trimnewline(line);
		if (line != NULL)
			i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_printf("i: %d\n", i);
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
	mlx_destroy_window(mlxstruct->mlx, mlxstruct->win);
	freemap(mlxstruct->map);
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
	if (mlxstruct->map[newy][newx] == 'C')
	{
		mlxstruct->collectiblesfound++;
		mlxstruct->map[newy][newx] = '0';
	}
	mlxstruct->playerx = newx;
	mlxstruct->playery = newy;
	printmap(mlxstruct);
	displaymap(mlxstruct);
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
			j++;
		}
		i++;
	}
}

void	setupmlx(t_game *mlxstruct, char **map)
{
	mlxstruct->mlx = mlx_init();
	mlxstruct->mapwidth = ft_strlen(map[0]);
	mlxstruct->mapheight = getmapheight(map);
	mlxstruct->win = mlx_new_window(mlxstruct->mlx, mlxstruct->mapwidth * 64, mlxstruct->mapheight * 64, "Hello world!");
	mlxstruct->map = map;
	getplayercollectwherabouts(mlxstruct);
	mlxstruct->playermoves = 0;
	mlxstruct->collectiblesfound = 0;
}

void	displaymap(t_game *mlxstruct)
{
	int		i;
	int		j;
	void	*img;
	int		iconwidth;
	int		iconheight;

	i = 0;
	while (mlxstruct->map[i] != NULL)
	{
		j = 0;
		while (mlxstruct->map[i][j])
		{
			img = mlx_xpm_file_to_image(mlxstruct->mlx, "./ground.xpm", &iconwidth, &iconheight);
			mlx_put_image_to_window(mlxstruct->mlx, mlxstruct->win, img, j * iconheight, i * iconwidth);
			if (mlxstruct->map[i][j] == '1')
				img = mlx_xpm_file_to_image(mlxstruct->mlx, "./wall.xpm", &iconwidth, &iconheight);
			if (mlxstruct->map[i][j] == 'C')
				img = mlx_xpm_file_to_image(mlxstruct->mlx, "./batterynew.xpm", &iconwidth, &iconheight);
			if (mlxstruct->map[i][j] == 'E')
				img = mlx_xpm_file_to_image(mlxstruct->mlx, "./factorynew.xpm", &iconwidth, &iconheight);
			mlx_put_image_to_window(mlxstruct->mlx, mlxstruct->win, img, j * iconheight, i * iconwidth);
			j++;
		}
		i++;
	}
	img = mlx_xpm_file_to_image(mlxstruct->mlx, "./robotnew.xpm", &iconwidth, &iconheight);
	mlx_put_image_to_window(mlxstruct->mlx, mlxstruct->win, img, mlxstruct->playerx * iconheight, mlxstruct->playery * iconwidth);
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
	mlx_loop(mlxstruct->mlx);
	return (0);
}


