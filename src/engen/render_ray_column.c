#include "../../includes/render_internal.h"

void	prepare_column(t_column *column, t_ray *ray, int x,
		t_texture *texture)
{
	column->x = x;
	column->draw_start = ray->draw_start;
	column->draw_end = ray->draw_end;
	column->line_height = ray->line_height;
	column->side = ray->side;
	column->texture = texture;
	column->wall_x = ray->wall_x;
}
