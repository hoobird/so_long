/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_stringstuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:27:40 by hulim             #+#    #+#             */
/*   Updated: 2024/05/14 22:08:51 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*so_trimfilename(char *filename)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(filename) - 1;
	while (so_isspacee(filename[i]))
		i++;
	while (j >= i && so_isspacee(filename[j]))
	{
		filename[j] = '\0';
		j--;
	}
	return (filename + i);
}

char	*so_trimnewline(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (line[i])
		i++;
	i--;
	while (i >= 0 && so_isspacee(line[i]))
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
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 4] != '.' || file[i - 3] != 'b' || file[i - 2] != 'e' || file[i
		- 1] != 'r')
		return (0);
	return (1);
}

int	so_isspacee(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
