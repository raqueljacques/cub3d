#include "../includes/cub3d.h"

static int is_wall(t_game *g, int mx, int my)
{
    if (my < 0 || my >= g->map_height || mx < 0 || mx >= g->map_width)
        return (1);
    return (g->map[my][mx] == TILE_WALL);
}

double cast_ray_column(t_game *game, t_vec2 dir, t_vec2 plane, int screen_x, int *out_side)
{
    double camera_x;
    double ray_x;
    double ray_y;
    int map_x;
    int map_y;
    double delta_x;
    double delta_y;
    double side_x;
    double side_y;
    int step_x;
    int step_y;
    int side;

    camera_x = 2.0 * screen_x / (double)WINDOW_WIDTH - 1.0;
    ray_x = dir.x + plane.x * camera_x;
    ray_y = dir.y + plane.y * camera_x;
    map_x = (int)game->player_x;
    map_y = (int)game->player_y;
    delta_x = (ray_x == 0.0) ? 1e30 : fabs(1.0 / ray_x);
    delta_y = (ray_y == 0.0) ? 1e30 : fabs(1.0 / ray_y);
    if (ray_x < 0)
    {
        step_x = -1;
        side_x = (game->player_x - map_x) * delta_x;
    }
    else
    {
        step_x = 1;
        side_x = (map_x + 1.0 - game->player_x) * delta_x;
    }
    if (ray_y < 0)
    {
        step_y = -1;
        side_y = (game->player_y - map_y) * delta_y;
    }
    else
    {
        step_y = 1;
        side_y = (map_y + 1.0 - game->player_y) * delta_y;
    }
    side = 0;
    while (!is_wall(game, map_x, map_y))
    {
        if (side_x < side_y)
        {
            side_x += delta_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_y += delta_y;
            map_y += step_y;
            side = 1;
        }
    }
    if (out_side)
        *out_side = side;
    if (side == 0)
        return ((map_x - game->player_x + (1 - step_x) / 2.0) / ray_x);
    else
        return ((map_y - game->player_y + (1 - step_y) / 2.0) / ray_y);
}
