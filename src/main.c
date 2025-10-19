/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:11:55 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/04 18:16:36 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
	{
		print_error("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}

	parse_and_validate(argv[1], &game);

	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
	{
		print_error("Erro ao inicializar MinilibX\n");
		free_game_data(&game);
		return (1);
	}
	game.win_ptr = mlx_new_window(game.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!game.win_ptr)
	{
		print_error("Erro ao criar janela\n");
		free_game_data(&game);
		return (1);
	}
	render_scene(&game);
	mlx_loop(game.mlx_ptr);

	free_game_data(&game);

	return (0);
}