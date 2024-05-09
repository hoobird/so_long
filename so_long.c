/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:11:36 by hulim             #+#    #+#             */
/*   Updated: 2024/05/10 04:09:09 by hulim            ###   ########.fr       */
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

void	printmap(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}

void	freemap(char **map)
{
	int		i;

	i = 0;
	while (map[i] != NULL)
	{
		ft_printf("freeing map[%d]\n", i);
		free(map[i]);
		ft_printf("freed map[%d]\n", i);
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

int	keybinds(int keycode, void *param)
{
	if (keycode == 65307)
		exit(0);
	ft_printf("keycode: %d\n", keycode);
	return (0);
}

int	destroy(int keycode, void *param)
{
	t_mlx	*mlxstruct;

	mlxstruct = (t_mlx *)param;
	mlx_destroy_window(mlxstruct->mlx, mlxstruct->win);
	// exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	char	**map;
	t_mlx	*mlxstruct;
	void	*img;
	int		width;
	int		height;

	if (argc != 2 || bercheck(trimfilename(argv[1])) == 0)
		return (printerror());
	map = readandvalidatemap(trimfilename(argv[1]));
	if (map == NULL)
		return (printerror());
	printmap(map);
	mlxstruct = malloc(sizeof(t_mlx));
	mlxstruct->mlx = mlx_init();
	mlxstruct->win = mlx_new_window(mlxstruct->mlx, 920, 640, "Hello world!");
	img = mlx_xpm_file_to_image(mlxstruct->mlx, "./factorynew.xpm", &width, &height);
	mlx_put_image_to_window(mlxstruct->mlx, mlxstruct->win, img, 0, 0);
	mlx_key_hook(mlxstruct->win, keybinds, 0);
	mlx_hook(mlxstruct->win, 17, 1L<<0, destroy, mlxstruct);
	mlx_loop(mlxstruct->mlx);
	freemap(map);
	return (0);
}


