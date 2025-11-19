/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:44:45 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/19 16:44:49 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_file_extension(const char *filename);
static void	validate_map(t_game *game);
static void	validate_map_content(t_game *game, int *player_count);

void	parse_and_validate(char *filename, t_game *game)
{
	int	fd;
	int	line_index;

	check_file_extension(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Error: Could not open the map file.\n", NULL);
	ft_bzero(game, sizeof(t_game));
	game->file_content = read_file_to_array(fd);
	close(fd);
	if (!game->file_content)
		exit_error("Error: File is empty or failed to read.\n", game);
	line_index = 0;
	parse_elements(&line_index, game);
	parse_map(&line_index, game);
	validate_map(game);
}

static void	check_file_extension(const char *filename)
{
	const char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
		exit_error("Error: Invalid file extension. Expected a .cub file.\n",
			NULL);
}

static void	validate_map(t_game *game)
{
	int	player_count;

	player_count = 0;
	if (!game->map || !game->map[0])
		exit_error("Error: Map is empty.\n", game);
	validate_map_content(game, &player_count);
	if (player_count != 1)
		exit_error("Error: Map must have exactly one starting position.\n",
			game);
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
				exit_error("Error: Invalid character in map.\n", game);
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
