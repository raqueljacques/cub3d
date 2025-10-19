#include "../includes/cub3d.h"

void    compute_dir_plane(char dir_char, t_vec2 *dir, t_vec2 *plane)
{
    dir->x = 0.0;
    dir->y = 0.0;
    plane->x = 0.0;
    plane->y = 0.0;
    if (dir_char == 'N')
    {
        dir->x = 0.0;
        dir->y = -1.0;
        plane->x = CAMERA_PLANE;
        plane->y = 0.0;
    }
    if (dir_char == 'S')
    {
        dir->x = 0.0;
        dir->y = 1.0;
        plane->x = -CAMERA_PLANE;
        plane->y = 0.0;
    }
    if (dir_char == 'E')
    {
        dir->x = 1.0;
        dir->y = 0.0;
        plane->x = 0.0;
        plane->y = CAMERA_PLANE;
    }
    if (dir_char == 'W')
    {
        dir->x = -1.0;
        dir->y = 0.0;
        plane->x = 0.0;
        plane->y = -CAMERA_PLANE;
    }
}
