/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:07:34 by rdos-san          #+#    #+#             */
/*   Updated: 2025/12/01 18:11:01 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**duplicate_map(t_game *game);
static int	flood_fill(char **map_copy, int y, int x, int height);
static int	get_map_height(char **map);
static void	check_unreachable_areas(t_game *g, char **map_c, int h);

void	validate_map_with_flood_fill(t_game *game)
{
	char	**map_copy;
	int		height;

	height = get_map_height(game->map);
	map_copy = duplicate_map(game);
	if (!map_copy)
	{
		exit_error("Error: Memory allocation failed for map copy.\n", game);
	}
	if (!flood_fill(map_copy, (int)game->player_y, (int)game->player_x, height))
	{
		free_split(map_copy);
		exit_error("Error: The map is not enclosed.\n", game);
	}
	check_unreachable_areas(game, map_copy, height);
	free_split(map_copy);
}

static void	check_unreachable_areas(t_game *game, char **map_copy, int height)
{
	int	y;
	int	x;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (ft_strchr("0NSEW", game->map[y][x]))
			{
				if (map_copy[y][x] != 'F')
				{
					if (!flood_fill(map_copy, y, x, height))
					{
						free_split(map_copy);
						exit_error("Error: Map has an open area.\n", game);
					}
				}
			}
		}
	}
}

static int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

static int	flood_fill(char **map_copy, int y, int x, int height)
{
	if (y < 0 || y >= height || x < 0 || !map_copy[y])
		return (0);
	if ((size_t)x >= ft_strlen(map_copy[y]))
		return (0);
	if (map_copy[y][x] == ' ' || map_copy[y][x] == '\0')
		return (0);
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return (1);
	map_copy[y][x] = 'F';
	if (!flood_fill(map_copy, y + 1, x, height))
		return (0);
	if (!flood_fill(map_copy, y - 1, x, height))
		return (0);
	if (!flood_fill(map_copy, y, x + 1, height))
		return (0);
	if (!flood_fill(map_copy, y, x - 1, height))
		return (0);
	return (1);
}

static char	**duplicate_map(t_game *game)
{
	char	**copy;
	int		i;

	i = 0;
	while (game->map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (game->map[i])
	{
		copy[i] = ft_strdup(game->map[i]);
		if (!copy[i])
		{
			free_split(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
