/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_maphelper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:36:22 by hulim             #+#    #+#             */
/*   Updated: 2024/05/14 22:06:55 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

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
		line = so_trimnewline(line);
		if (line != NULL)
			i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	check_symbol(char symbol, int *player, int *exit, int *collectible)
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

void	*freemap(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
	return (NULL);
}

int	getmapheight(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}
