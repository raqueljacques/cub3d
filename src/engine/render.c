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

static int  imax(int a, int b) { return a > b ? a : b; }
static int  imin(int a, int b) { return a < b ? a : b; }

static void draw_rect(t_img *img, int x, int y, int w, int h, unsigned int color)
{
    int i, j;
    for (j = 0; j < h; ++j)
        for (i = 0; i < w; ++i)
            put_pixel(img, x + i, y + j, color);
}

static void draw_line(t_img *img, int x0, int y0, int x1, int y1, unsigned int color)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        put_pixel(img, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

static void draw_minimap(t_game *g, t_img *img)
{
    int margin = 8;
    int max_w = WINDOW_WIDTH / 3;
    int max_h = WINDOW_HEIGHT / 3;
    if (g->map_width <= 0 || g->map_height <= 0)
        return;
    int tile_x = imax(2, max_w / g->map_width);
    int tile_y = imax(2, max_h / g->map_height);
    int tile = imin(tile_x, tile_y);
    int ox = margin;
    int oy = margin;

    // Tiles
    for (int my = 0; my < g->map_height; ++my)
    {
        for (int mx = 0; mx < g->map_width; ++mx)
        {
            unsigned int color;
            char c = g->map[my][mx];
            if (c == TILE_WALL)
                color = 0x222222; // wall
            else if (c == ' ')
                color = 0x000000; // void/outside
            else
                color = 0x999999; // walkable
            draw_rect(img, ox + mx * tile, oy + my * tile, tile, tile, color);
        }
    }

    // Player
    int px = ox + (int)(g->player_x * tile);
    int py = oy + (int)(g->player_y * tile);
    int psize = imax(2, tile / 3);
    draw_rect(img, px - psize/2, py - psize/2, psize, psize, 0xFF0000);

    // Direction line
    double dir_x, dir_y, plane_x, plane_y;
    engine_get_dir_plane(&dir_x, &dir_y, &plane_x, &plane_y);
    (void)plane_x; (void)plane_y;
    int lx = px + (int)(dir_x * tile * 2.5);
    int ly = py + (int)(dir_y * tile * 2.5);
    draw_line(img, px, py, lx, ly, 0xFF0000);
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

    // Minimap overlay (top-left)
    draw_minimap(g, &img);
    mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, img.img, 0, 0);
}
