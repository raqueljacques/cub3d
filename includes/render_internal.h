/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:06:24 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/19 19:06:26 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_INTERNAL_H
# define RENDER_INTERNAL_H

# include "cub3d.h"

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		delta_x;
	double		delta_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	double		perp_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
}				t_ray;

typedef struct s_column
{
	int			x;
	int			draw_start;
	int			draw_end;
	int			line_height;
	int			side;
	t_texture	*texture;
	double		wall_x;
}				t_column;

typedef struct s_sample
{
	int			tex_x;
	double		step;
	double		tex_pos;
}				t_sample;

void			draw_background(t_game *game);
void			draw_wall_slice(t_game *game, t_column *column);
char			map_tile(t_game *game, int x, int y);
t_texture		*select_texture(t_game *game, int side, double ray_dir_x,
					double ray_dir_y);
void			init_ray(t_ray *ray, t_player *player, int column);
void			setup_steps(t_ray *ray, t_player *player);
void			perform_dda(t_ray *ray, t_game *game);
void			set_perp_distance(t_ray *ray, t_player *player);
void			set_slice_limits(t_ray *ray);
void			set_wall_hit(t_ray *ray, t_player *player);
void			prepare_column(t_column *column, t_ray *ray, int x,
					t_texture *texture);

#endif
