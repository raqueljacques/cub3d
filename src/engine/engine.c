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

typedef struct s_keys
{
    int w;
    int a;
    int s;
    int d;
    int left;
    int right;
}   t_keys;

static t_keys g_keys;

static int  close_hook(t_game *g)
{
    (void)g;
    exit(0);
}

static void move_straight(t_game *g, double dx, double dy)
{
    double nx = g->player_x + dx * MOVE_SPEED;
    double ny = g->player_y + dy * MOVE_SPEED;
    if (g->map[(int)g->player_y][(int)nx] != TILE_WALL) g->player_x = nx;
    if (g->map[(int)ny][(int)g->player_x] != TILE_WALL) g->player_y = ny;
}

static void move_strafe(t_game *g, double px, double py)
{
    double nx = g->player_x + px * MOVE_SPEED;
    double ny = g->player_y + py * MOVE_SPEED;
    if (g->map[(int)g->player_y][(int)nx] != TILE_WALL) g->player_x = nx;
    if (g->map[(int)ny][(int)g->player_x] != TILE_WALL) g->player_y = ny;
}

static void rotate_dir_plane(double ang)
{
    double dir_x, dir_y, plane_x, plane_y;
    double old_dx, old_px;

    engine_get_dir_plane(&dir_x, &dir_y, &plane_x, &plane_y);
    old_dx = dir_x;
    dir_x = dir_x * cos(ang) - dir_y * sin(ang);
    dir_y = old_dx * sin(ang) + dir_y * cos(ang);
    old_px = plane_x;
    plane_x = plane_x * cos(ang) - plane_y * sin(ang);
    plane_y = old_px * sin(ang) + plane_y * cos(ang);
    engine_set_dir_plane(dir_x, dir_y, plane_x, plane_y);
}

static int  key_press(int key, t_game *g)
{
    if (key == KEY_ESC)
        exit(0);
    if (key == KEY_W) g_keys.w = 1;
    if (key == KEY_S) g_keys.s = 1;
    if (key == KEY_A) g_keys.a = 1;
    if (key == KEY_D) g_keys.d = 1;
    if (key == KEY_LEFT) g_keys.left = 1;
    if (key == KEY_RIGHT) g_keys.right = 1;
    return (0);
}

static int  key_release(int key, t_game *g)
{
    (void)g;
    if (key == KEY_W) g_keys.w = 0;
    if (key == KEY_S) g_keys.s = 0;
    if (key == KEY_A) g_keys.a = 0;
    if (key == KEY_D) g_keys.d = 0;
    if (key == KEY_LEFT) g_keys.left = 0;
    if (key == KEY_RIGHT) g_keys.right = 0;
    return (0);
}

static int  loop_hook(t_game *g)
{
    double dir_x, dir_y, plane_x, plane_y;
    engine_get_dir_plane(&dir_x, &dir_y, &plane_x, &plane_y);

    if (g_keys.w) move_straight(g, dir_x, dir_y);
    if (g_keys.s) move_straight(g, -dir_x, -dir_y);
    if (g_keys.a) move_strafe(g, -plane_x, -plane_y);
    if (g_keys.d) move_strafe(g, plane_x, plane_y);
    if (g_keys.left) rotate_dir_plane(ROT_SPEED);
    if (g_keys.right) rotate_dir_plane(-ROT_SPEED);

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
    // Key press and release events
    mlx_hook(g->win_ptr, 2, 1L<<0, key_press, g);
    mlx_hook(g->win_ptr, 3, 1L<<1, key_release, g);
    // Continuous loop to update movement
    mlx_loop_hook(g->mlx_ptr, loop_hook, g);
    mlx_hook(g->win_ptr, 17, 0, close_hook, g);
    mlx_loop(g->mlx_ptr);
}
