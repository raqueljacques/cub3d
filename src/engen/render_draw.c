/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:45:54 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/19 16:45:59 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render_internal.h"

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

void	draw_background(t_game *game)
{
	int	y;
	int	x;

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

static int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;

	pixel = texture->addr + tex_y * texture->size_line + tex_x * (texture->bpp
			/ 8);
	return (*(int *)pixel);
}

static void	init_sample(t_sample *sample, t_column *column)
{
	sample->tex_x = (int)(column->wall_x * column->texture->width);
	if (sample->tex_x < 0)
		sample->tex_x = 0;
	if (sample->tex_x >= column->texture->width)
		sample->tex_x = column->texture->width - 1;
	sample->step = (double)column->texture->height / column->line_height;
	sample->tex_pos = (column->draw_start - WIN_HEIGHT / 2 + column->line_height
			/ 2) * sample->step;
}

void	draw_wall_slice(t_game *game, t_column *column)
{
	t_sample	sample;
	int			current;
	int			tex_y;
	int			color;

	init_sample(&sample, column);
	current = column->draw_start;
	while (current <= column->draw_end)
	{
		tex_y = (int)sample.tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= column->texture->height)
			tex_y = column->texture->height - 1;
		sample.tex_pos += sample.step;
		color = get_texture_color(column->texture, sample.tex_x, tex_y);
		if (column->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(game, column->x, current, color);
		current++;
	}
}
