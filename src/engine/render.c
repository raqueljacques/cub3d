#include "../includes/cub3d.h"

void render_scene(t_game *game)
{
    int x;
    t_vec2 dir;
    t_vec2 plane;
    int side;
    double dist;
    int line_height;
    int draw_start;
    int draw_end;

    compute_dir_plane(game->player_dir, &dir, &plane);
    x = 0;
    while (x < WINDOW_WIDTH)
    {
        dist = cast_ray_column(game, dir, plane, x, &side);
        if (dist <= 0.0)
            dist = 0.1;
        line_height = (int)(WINDOW_HEIGHT / dist);
        draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_end >= WINDOW_HEIGHT)
            draw_end = WINDOW_HEIGHT - 1;
        // Desenha a linha vertical da parede
        mlx_draw_wall_column(game->mlx_ptr, game->win_ptr, x, draw_start, draw_end, side);
        x++;
    }
}
