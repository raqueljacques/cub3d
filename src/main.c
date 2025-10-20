/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:11:55 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/04 18:16:36 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <unistd.h>


void put_pix(int x, int y, int color, t_game *game)
{
	if(x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return ;
	int index;
	index = y *game->size_line + x * game->bpp /8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}
void draw_square(int x, int y, int size, int color, t_game *game)
{
    for(int i = 0; i < size; i++)
        put_pix(x + i, y, color, game);
    for(int i = 0; i < size; i++)
        put_pix(x, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pix(x + size, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pix(x + i, y + size, color, game);
}

void	init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game->data = mlx_get_data_addr(game->img_ptr, &game->bpp, &game->size_line,&game->endian);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	
}
int	main(int argc, char **argv)
{
	t_game game;
	(void)argc;
	/*if (argc != 2)
	{
		print_error("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}*/

	parse_and_validate(argv[1], &game);
	init_game(&game);
	draw_square(WIN_WIDTH / 2, 	WIN_HEIGHT / 2, 10, 0x00FF00, &game);
	mlx_loop(game.mlx_ptr);
	
	return (0);
}