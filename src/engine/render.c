/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacarla <student@42>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 00:00:00 by anacarla          #+#    #+#             */
/*   Updated: 2025/10/19 00:00:00 by anacarla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

static void put_pixel(t_img *img, int x, int y, unsigned int color)
{
    char *dst;

    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

static void fill_background(t_img *img, unsigned int ceil_color, unsigned int floor_color)
{
    int y;
    int x;

    for (y = 0; y < WINDOW_HEIGHT / 2; ++y)
        for (x = 0; x < WINDOW_WIDTH; ++x)
            put_pixel(img, x, y, ceil_color);
    for (; y < WINDOW_HEIGHT; ++y)
        for (x = 0; x < WINDOW_WIDTH; ++x)
            put_pixel(img, x, y, floor_color);
}

static unsigned int wall_color_from_side(int side)
{
    return side ? 0x0088FF : 0x0044AA; // darker for y-side
}

void    render_frame(t_game *g)
{
    static t_img img;
    double dir_x, dir_y, plane_x, plane_y;

    if (!img.img)
    {
        img.img = mlx_new_image(g->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
        img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
    }

    engine_get_dir_plane(&dir_x, &dir_y, &plane_x, &plane_y);
    fill_background(&img, g->ceiling_color, g->floor_color);

    for (int x = 0; x < WINDOW_WIDTH; ++x)
    {
        int side = 0;
        double dist = cast_ray_column(g, dir_x, dir_y, plane_x, plane_y, x, &side);
        if (dist <= 0.0001)
            continue;
        int line_h = (int)(WINDOW_HEIGHT / dist);
        int draw_start = -line_h / 2 + WINDOW_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_h / 2 + WINDOW_HEIGHT / 2;
        if (draw_end >= WINDOW_HEIGHT) draw_end = WINDOW_HEIGHT - 1;
        unsigned int color = wall_color_from_side(side);
        for (int y = draw_start; y <= draw_end; ++y)
            put_pixel(&img, x, y, color);
    }

    mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, img.img, 0, 0);
}
