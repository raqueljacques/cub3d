/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacarla <student@42>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 00:00:00 by anacarla          #+#    #+#             */
/*   Updated: 2025/10/19 00:00:00 by anacarla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int  close_hook(t_game *g)
{
    (void)g;
    exit(0);
}

static int  key_hook(int key, t_game *g)
{
    double dir_x, dir_y, plane_x, plane_y;
    engine_get_dir_plane(&dir_x, &dir_y, &plane_x, &plane_y);

    if (key == KEY_ESC)
        exit(0);
    if (key == KEY_W)
    {
        double nx = g->player_x + dir_x * MOVE_SPEED;
        double ny = g->player_y + dir_y * MOVE_SPEED;
        if (g->map[(int)g->player_y][(int)nx] != TILE_WALL) g->player_x = nx;
        if (g->map[(int)ny][(int)g->player_x] != TILE_WALL) g->player_y = ny;
    }
    if (key == KEY_S)
    {
        double nx = g->player_x - dir_x * MOVE_SPEED;
        double ny = g->player_y - dir_y * MOVE_SPEED;
        if (g->map[(int)g->player_y][(int)nx] != TILE_WALL) g->player_x = nx;
        if (g->map[(int)ny][(int)g->player_x] != TILE_WALL) g->player_y = ny;
    }
    if (key == KEY_A)
    {
        double nx = g->player_x - plane_x * MOVE_SPEED;
        double ny = g->player_y - plane_y * MOVE_SPEED;
        if (g->map[(int)g->player_y][(int)nx] != TILE_WALL) g->player_x = nx;
        if (g->map[(int)ny][(int)g->player_x] != TILE_WALL) g->player_y = ny;
    }
    if (key == KEY_D)
    {
        double nx = g->player_x + plane_x * MOVE_SPEED;
        double ny = g->player_y + plane_y * MOVE_SPEED;
        if (g->map[(int)g->player_y][(int)nx] != TILE_WALL) g->player_x = nx;
        if (g->map[(int)ny][(int)g->player_x] != TILE_WALL) g->player_y = ny;
    }
    if (key == KEY_LEFT || key == KEY_RIGHT)
    {
        double ang = (key == KEY_LEFT) ? ROT_SPEED : -ROT_SPEED;
        double old_dx = dir_x;
        dir_x = dir_x * cos(ang) - dir_y * sin(ang);
        dir_y = old_dx * sin(ang) + dir_y * cos(ang);
        double old_px = plane_x;
        plane_x = plane_x * cos(ang) - plane_y * sin(ang);
        plane_y = old_px * sin(ang) + plane_y * cos(ang);
        engine_set_dir_plane(dir_x, dir_y, plane_x, plane_y);
    }
    render_frame(g);
    return (0);
}

void    start_engine(t_game *g)
{
    double dir_x, dir_y, plane_x, plane_y;

    compute_dir_plane(g->player_dir, &dir_x, &dir_y, &plane_x, &plane_y);
    engine_set_dir_plane(dir_x, dir_y, plane_x, plane_y);

    g->mlx_ptr = mlx_init();
    if (!g->mlx_ptr)
        exit(1);
    g->win_ptr = mlx_new_window(g->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
    if (!g->win_ptr)
        exit(1);

    render_frame(g);
    mlx_hook(g->win_ptr, 2, 1L<<0, key_hook, g);
    mlx_hook(g->win_ptr, 17, 0, close_hook, g);
    mlx_loop(g->mlx_ptr);
}
