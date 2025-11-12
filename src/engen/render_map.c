#include "../../includes/render_internal.h"

char	map_tile(t_game *game, int x, int y)
{
	size_t	len;

	if (x < 0 || y < 0 || y >= game->map_height)
		return ('1');
	if (!game->map[y])
		return ('1');
	len = ft_strlen(game->map[y]);
	if (x >= (int)len)
		return ('1');
	if (game->map[y][x] == ' ')
		return ('1');
	return (game->map[y][x]);
}

t_texture	*select_texture(t_game *game, int side,
		double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (&game->west_texture);
		return (&game->east_texture);
	}
	if (ray_dir_y > 0)
		return (&game->north_texture);
	return (&game->south_texture);
}
