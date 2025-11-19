/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_orientation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:46:12 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/19 19:02:29 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_direction(t_player *player, double dx, double dy)
{
	player->dir_x = dx;
	player->dir_y = dy;
}

static void	set_plane(t_player *player, double px, double py)
{
	player->plane_x = px;
	player->plane_y = py;
}

static void	set_orientation(t_player *player, char dir)
{
	if (dir == 'N')
	{
		set_direction(player, 0, -1);
		set_plane(player, CAMERA_PLANE, 0);
	}
	else if (dir == 'S')
	{
		set_direction(player, 0, 1);
		set_plane(player, -CAMERA_PLANE, 0);
	}
	else if (dir == 'E')
	{
		set_direction(player, 1, 0);
		set_plane(player, 0, CAMERA_PLANE);
	}
	else
	{
		set_direction(player, -1, 0);
		set_plane(player, 0, -CAMERA_PLANE);
	}
}

void	player_start(t_game *game)
{
	t_player	*player;

	player = &game->player;
	player->x = game->player_x;
	player->y = game->player_y;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->turn_left = false;
	player->turn_right = false;
	set_orientation(player, game->player_dir);
}
