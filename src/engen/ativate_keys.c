/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ativate_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:52:02 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/19 18:52:24 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	pressing_keys(int key, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (key == KEY_ESC || key == KEY_C)
		cleanup_and_exit(game, EXIT_SUCCESS);
	if (key == W)
		player->key_up = true;
	if (key == S)
		player->key_down = true;
	if (key == A)
		player->key_left = true;
	if (key == D)
		player->key_right = true;
	if (key == LEFT)
		player->turn_left = true;
	if (key == RIGHT)
		player->turn_right = true;
	return (0);
}

int	release_keys(int key, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (key == W)
		player->key_up = false;
	if (key == S)
		player->key_down = false;
	if (key == A)
		player->key_left = false;
	if (key == D)
		player->key_right = false;
	if (key == LEFT)
		player->turn_left = false;
	if (key == RIGHT)
		player->turn_right = false;
	return (0);
}
