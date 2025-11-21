/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:11:55 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/21 15:28:52 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L << 0, pressing_keys, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, release_keys, game);
	mlx_hook(game->win_ptr, 17, 0, handle_close, game);
	mlx_loop_hook(game->mlx_ptr, render_scene, game);
}

static void	init_mlx_core(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		print_error("Error: Failed to initialize MLX.\n");
		exit(EXIT_FAILURE);
	}
}

static void	init_window_and_image(t_game *game)
{
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"Cub3d");
	if (!game->win_ptr)
	{
		print_error("Error: Failed to create window.\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img_ptr)
	{
		print_error("Error: Failed to create image buffer.\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
	game->data = mlx_get_data_addr(game->img_ptr, &game->bpp, &game->size_line,
			&game->endian);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}
	parse_and_validate(argv[1], &game);
	init_mlx_core(&game);
	load_textures(&game);
	init_window_and_image(&game);
	player_start(&game);
	init_hooks(&game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
