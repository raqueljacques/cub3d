#include "../../includes/cub3d.h"

static void	put_pixel(t_game *game, int x, int y, int color)
{
	int	index;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	index = y * game->size_line + x * (game->bpp / 8);
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

static void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel(game, x, y, game->ceiling_color);
			else
				put_pixel(game, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

static char	map_tile(t_game *game, int x, int y)
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

static t_texture	*select_texture(t_game *game, int side,
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

static int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;

	pixel = texture->addr + (tex_y * texture->size_line)
		+ (tex_x * (texture->bpp / 8));
	return (*(int *)pixel);
}

static void	draw_wall_slice(t_game *game, int x, int draw_start, int draw_end,
		int side, t_texture *texture, double wall_x)
{
	double	step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
	int		line_height;
	int		color;

	line_height = draw_end - draw_start + 1;
	tex_x = (int)(wall_x * texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	step = (double)texture->height / line_height;
	tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;
	while (draw_start <= draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		tex_pos += step;
		color = get_texture_color(texture, tex_x, tex_y);
		if (side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(game, x, draw_start, color);
		draw_start++;
	}
}

static void	cast_rays(t_game *game)
{
	t_player	*player;
	int			x;

	player = &game->player;
	x = 0;
	while (x < WIN_WIDTH)
	{
		double	camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
		double	ray_dir_x = player->dir_x + player->plane_x * camera_x;
		double	ray_dir_y = player->dir_y + player->plane_y * camera_x;
		int		map_x = (int)player->x;
		int		map_y = (int)player->y;
		double	delta_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
		double	delta_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);
		double	side_dist_x;
		double	side_dist_y;
		int		step_x;
		int		step_y;
		int		hit;
		int		side;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (player->x - map_x) * delta_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - player->x) * delta_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (player->y - map_y) * delta_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - player->y) * delta_y;
		}
		hit = 0;
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_y;
				map_y += step_y;
				side = 1;
			}
			if (map_tile(game, map_x, map_y) == '1')
				hit = 1;
		}
		double	perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (map_x - player->x + (1 - step_x) / 2.0) / ray_dir_x;
		else
			perp_wall_dist = (map_y - player->y + (1 - step_y) / 2.0) / ray_dir_y;
		if (perp_wall_dist < 0.0001)
			perp_wall_dist = 0.0001;
		int		line_height = (int)(WIN_HEIGHT / perp_wall_dist);
		int		draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		int		draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		t_texture	*texture = select_texture(game, side, ray_dir_x, ray_dir_y);
		double	wall_x;
		if (side == 0)
			wall_x = player->y + perp_wall_dist * ray_dir_y;
		else
			wall_x = player->x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);
		if (side == 0 && ray_dir_x > 0)
			wall_x = 1.0 - wall_x;
		if (side == 1 && ray_dir_y < 0)
			wall_x = 1.0 - wall_x;
		draw_wall_slice(game, x, draw_start, draw_end, side, texture, wall_x);
		x++;
	}
}

int	render_scene(t_game *game)
{
	move_player(game);
	draw_background(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}
