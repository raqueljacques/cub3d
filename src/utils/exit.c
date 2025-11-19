/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:47:38 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/19 16:58:39 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	destroy_mlx_handles(t_game *game)
{
	if (game->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->img_ptr);
		game->img_ptr = NULL;
	}
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
}

void	cleanup_and_exit(t_game *game, int code)
{
	if (!game)
		exit(code);
	free_game_data(game);
	destroy_mlx_handles(game);
	exit(code);
}

int	handle_close(t_game *game)
{
	cleanup_and_exit(game, EXIT_SUCCESS);
	return (0);
}
