/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_column.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:45:48 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/19 16:45:49 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
