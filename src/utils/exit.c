#include "../../includes/cub3d.h"

static void	destroy_mlx_handles(t_game *game)
{
	if (game->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->img_ptr);
		game->img_ptr = NULL;
	}
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
#ifdef __linux__
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
#endif
}

void	cleanup_and_exit(t_game *game, int code)
{
	if (!game)
		exit(code);
	free_game_data(game);
	destroy_mlx_handles(game);
	exit(code);
}

int	handle_close(t_game *game)
{
	cleanup_and_exit(game, EXIT_SUCCESS);
	return (0);
}
