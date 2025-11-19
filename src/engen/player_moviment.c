/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moviment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:54:15 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/19 18:54:54 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_walkable(t_game *game, double x, double y)
{
	int		map_x;
	int		map_y;
	size_t	len;
	char	tile;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_y >= game->map_height)
		return (0);
	if (!game->map[map_y])
		return (0);
	len = ft_strlen(game->map[map_y]);
	if (map_x >= (int)len)
		return (0);
	tile = game->map[map_y][map_x];
	if (tile == '1' || tile == ' ')
		return (0);
	return (1);
}

static void	move_forward_backward(t_game *game, double speed)
{
	t_player	*player;
	double		new_x;
	double		new_y;

	player = &game->player;
	new_x = player->x + player->dir_x * speed;
	new_y = player->y + player->dir_y * speed;
	if (is_walkable(game, new_x, player->y))
		player->x = new_x;
	if (is_walkable(game, player->x, new_y))
		player->y = new_y;
}

static void	move_strafe(t_game *game, double speed)
{
	t_player	*player;
	double		perp_x;
	double		perp_y;
	double		new_x;
	double		new_y;

	player = &game->player;
	perp_x = -player->dir_y;
	perp_y = player->dir_x;
	new_x = player->x + perp_x * speed;
	new_y = player->y + perp_y * speed;
	if (is_walkable(game, new_x, player->y))
		player->x = new_x;
	if (is_walkable(game, player->x, new_y))
		player->y = new_y;
}

static void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos_a - player->dir_y * sin_a;
	player->dir_y = old_dir_x * sin_a + player->dir_y * cos_a;
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos_a - player->plane_y * sin_a;
	player->plane_y = old_plane_x * sin_a + player->plane_y * cos_a;
}

void	move_player(t_game *game)
{
	t_player	*player;
	double		move_speed;
	double		rot_speed;

	player = &game->player;
	move_speed = MOVE_SPEED;
	rot_speed = ROT_SPEED;
	if (player->key_up)
		move_forward_backward(game, move_speed);
	if (player->key_down)
		move_forward_backward(game, -move_speed);
	if (player->key_left)
		move_strafe(game, -move_speed);
	if (player->key_right)
		move_strafe(game, move_speed);
	if (player->turn_left)
		rotate_player(player, -rot_speed);
	if (player->turn_right)
		rotate_player(player, rot_speed);
}
