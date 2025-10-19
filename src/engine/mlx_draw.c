#include "../includes/cub3d.h"

// Função stub para desenhar coluna de parede (substitua por textura depois)
void mlx_draw_wall_column(void *mlx_ptr, void *win_ptr, int x, int start, int end, int side)
{
    int y = start;
    int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;
    while (y <= end)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
        y++;
    }
}
