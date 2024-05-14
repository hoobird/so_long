/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_mapvalidate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:31:51 by hulim             #+#    #+#             */
/*   Updated: 2024/05/14 21:33:36 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

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
		line = so_trimnewline(line);
		if (line != NULL)
			map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	if (validatemap(map) == 0)
		return (freemap(map));
	return (map);
}

int	validatemap(char **map)
{
	if (checkmaprect(map) == 0 || checkmapborder(map) == 0
		|| checkmapcontent(map) == 0)
		return (0);
	return (1);
}

int	checkmaprect(char **map)
{
	int	i;
	int	j;
	int	len;

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
	int	i;
	int	j;
	int	height;

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

int	checkmapcontent(char **map)
{
	int	i;
	int	j;
	int	player;
	int	exit;
	int	collectible;

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
