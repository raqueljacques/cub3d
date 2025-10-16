/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:25:44 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/16 17:54:06 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_file_extension(const char *filename);
static void	validate_map(t_game *game);
static void	validate_map_content(t_game *game, int *player_count);

void	parse_and_validate(char *filename, t_game *game)
{
	int	fd;

	check_file_extension(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Error: Could not open the map file.\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(game, sizeof(t_game));
	parse_elements(fd, game);
	parse_map(fd, game);
	validate_map(game);
	close(fd);
}

static void	check_file_extension(const char *filename)
{
	const char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
	{
		print_error("Error: Invalid file extension. Expected a .cub file.\n");
		exit(EXIT_FAILURE);
	}
}

static void	validate_map(t_game *game)
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
				game->player_x = x + 0.5;
				game->player_y = y + 0.5;
				game->player_dir = game->map[y][x];
				(*player_count)++;
			}
		}
	}
}
