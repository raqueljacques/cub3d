/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:57:27 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/04 17:05:44 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**duplicate_map(t_game *game);
static void	flood_fill(char **map_copy, int y, int x, int height);

void	validate_map_with_flood_fill(t_game *game)
{
	char	**map_copy;
	int		height;

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
	flood_fill(map_copy, (int)game->player_y, (int)game->player_x, height);
	free_split(map_copy);
}

static void	flood_fill(char **map_copy, int y, int x, int height)
{
	// Condição de parada: Se atingir a borda do mapa é pq ta aberto.
	if (y < 0 || y >= height || x < 0 || !map_copy[y][x])
	{
		print_error("Error: Map is open. Flood fill reached the edge.\n");
		free_split(map_copy);
		exit(EXIT_FAILURE);
	}
	// Condição de parada: Se encontrar uma parede ('1') ou já foi preenchido ('F')
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return ;
	// Condição de erro: Se encontrar um espaço é pq tem um buraco no mapa
	if (map_copy[y][x] == ' ')
	{
		print_error("Error: Map is open. Path leads to an empty space.\n");
		free_split(map_copy);
		exit(EXIT_FAILURE);
	}
	// Marca a atual como preenchida
	map_copy[y][x] = 'F';
	// Chama recursivamente para as 4 direções
	flood_fill(map_copy, y + 1, x, height);
	flood_fill(map_copy, y - 1, x, height);
	flood_fill(map_copy, y, x + 1, height);
	flood_fill(map_copy, y, x - 1, height);
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
