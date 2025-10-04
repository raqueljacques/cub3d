/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:11:16 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/04 17:04:45 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	validate_map_content(t_game *game, int *player_count);

void	parse_map(int fd, t_game *game)
{
	char	*line;
	char	*map_buffer;
	char	*temp;

	map_buffer = ft_strdup("");
	while ((line = get_next_line(fd)))
	{
		if (*line == '\n' && *map_buffer == '\0')
		{
			free(line);
			continue ;
		}
		temp = map_buffer;
		map_buffer = ft_strjoin(map_buffer, line);
		free(temp);
		free(line);
	}
	if (*map_buffer == '\0')
	{
		print_error("Error: Map not found in the file.\n");
		exit(EXIT_FAILURE);
	}
	game->map = ft_split(map_buffer, '\n');
	free(map_buffer);
}

void	validate_map(t_game *game)
{
	int	player_count;

	player_count = 0;
	if (!game->map || !game->map[0])
	{
		print_error("Error: Map is empty.\n");
		exit(EXIT_FAILURE);
	}
	validate_map_content(game, &player_count);
	if (player_count != 1)
	{
		print_error("Error: Map must have exactly one starting position.\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
	validate_map_with_flood_fill(game);
}

static void	validate_map_content(t_game *game, int *player_count)
{
	int	y;
	int	x;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (ft_strchr(" 01NSEW", game->map[y][x]) == NULL)
			{
				print_error("Error: Invalid character in map.\n");
				exit(EXIT_FAILURE);
			}
			if (ft_strchr("NSEW", game->map[y][x]))
			{
				// Posiciona o jogador no centro da célula do mapa
				game->player_x = x + 0.5;
				game->player_y = y + 0.5;
				game->player_dir = game->map[y][x];
				(*player_count)++;
			}
		}
	}
}
