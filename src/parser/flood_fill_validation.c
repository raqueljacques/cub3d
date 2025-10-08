/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:57:27 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/08 10:53:41 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**duplicate_map(t_game *game);
static int	flood_fill(char **map_copy, int y, int x, int height);

void	validate_map_with_flood_fill(t_game *game)
{
	char	**map_copy;
	int		height;
	int		is_valid;

	height = 0;
	while (game->map[height])
		height++;
	map_copy = duplicate_map(game);
	if (!map_copy)
	{
		print_error("Error: Memory allocation failed for map copy.\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
	is_valid = flood_fill(map_copy, (int)game->player_y, (int)game->player_x,
			height);
	free_split(map_copy);
	if (!is_valid)
	{
		print_error("Error: The map is not enclosed by walls.\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
}

static int	flood_fill(char **map_copy, int y, int x, int height)
{
	// Condição de parada: Se atingir a borda do mapa é pq ta aberto.
	if (y < 0 || y >= height || x < 0 || !map_copy[y] || !map_copy[y][x]
		|| map_copy[y][x] == ' ')
		return (0);
	// Condição de parada: Se encontrar uma parede ('1') ou já foi preenchido ('F')
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
	int	i;

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