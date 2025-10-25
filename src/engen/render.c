#include "../../includes/render_internal.h"

static void	render_column(t_game *game, t_ray *ray, int x)
{
	t_column	column;
	t_texture	*texture;

	texture = select_texture(game, ray->side, ray->dir_x, ray->dir_y);
	prepare_column(&column, ray, x, texture);
	draw_wall_slice(game, &column);
}

static void	cast_rays(t_game *game)
{
	t_player	*player;
	t_ray		ray;
	int			x;

	player = &game->player;
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, player, x);
		setup_steps(&ray, player);
		perform_dda(&ray, game);
		set_perp_distance(&ray, player);
		set_slice_limits(&ray);
		set_wall_hit(&ray, player);
		render_column(game, &ray, x);
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
