/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:11:55 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/16 17:50:34 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}
	parse_and_validate(argv[1], &game);
	printf("Parser validation successful!\n");
	printf("North texture path: %s\n", game.north_texture);
	printf("South texture path: %s\n", game.south_texture);
	printf("West texture path: %s\n", game.west_texture);
	printf("East texture path: %s\n", game.east_texture);
	printf("Floor color: %d\n", game.floor_color);
	printf("Ceiling color: %d\n", game.ceiling_color);
	printf("Player start position: (%.1f, %.1f) facing %c\n", game.player_y,
		game.player_x, game.player_dir);
	free_game_data(&game);
	return (0);
}
