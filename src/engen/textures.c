#include "../../includes/cub3d.h"

static void	load_texture(t_game *game, t_texture *texture)
{
	if (!texture->path)
	{
		print_error("Error: Missing texture path.\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
	texture->img = mlx_xpm_file_to_image(game->mlx_ptr, texture->path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		print_error("Error: Failed to load texture: ");
		print_error(texture->path);
		print_error("\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	if (!texture->addr)
	{
		print_error("Error: Failed to access texture data.\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->north_texture);
	load_texture(game, &game->south_texture);
	load_texture(game, &game->west_texture);
	load_texture(game, &game->east_texture);
}
