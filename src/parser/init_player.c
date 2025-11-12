#include "../../includes/cub3d.h"

void    init_player_from_map(t_game *game)
{
    int y;
    int x;
    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            char c;
            c = game->map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                game->player_x = x + 0.5;
                game->player_y = y + 0.5;
                game->player_dir = c;
                return;
            }
            x = x + 1;
        }
        y = y + 1;
    }
}
