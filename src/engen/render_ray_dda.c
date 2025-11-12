#include "../../includes/render_internal.h"

void	perform_dda(t_ray *ray, t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map_tile(game, ray->map_x, ray->map_y) == '1')
			hit = 1;
	}
}

void	set_perp_distance(t_ray *ray, t_player *player)
{
	double	offset;

	if (ray->side == 0)
		offset = ray->map_x - player->x + (1 - ray->step_x) / 2.0;
	else
		offset = ray->map_y - player->y + (1 - ray->step_y) / 2.0;
	if (ray->side == 0)
		ray->perp_dist = offset / ray->dir_x;
	else
		ray->perp_dist = offset / ray->dir_y;
	if (ray->perp_dist < 0.0001)
		ray->perp_dist = 0.0001;
}

void	set_slice_limits(t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	set_wall_hit(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_x = player->y + ray->perp_dist * ray->dir_y;
	else
		ray->wall_x = player->x + ray->perp_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->wall_x = 1.0 - ray->wall_x;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->wall_x = 1.0 - ray->wall_x;
}
