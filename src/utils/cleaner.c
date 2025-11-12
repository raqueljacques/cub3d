/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:57:53 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/12 15:12:07 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	destroy_texture(t_game *game, t_texture *texture)
{
	if (texture->img && game->mlx_ptr)
		mlx_destroy_image(game->mlx_ptr, texture->img);
	if (texture->path)
	{
		free(texture->path);
		texture->path = NULL;
	}
	texture->img = NULL;
	texture->addr = NULL;
}

void	free_game_data(t_game *game)
{
	destroy_texture(game, &game->north_texture);
	destroy_texture(game, &game->south_texture);
	destroy_texture(game, &game->west_texture);
	destroy_texture(game, &game->east_texture);
	if (game->map)
		free_split(game->map);
	if (game->file_content)
		free_split(game->file_content);
}

void	free_split(char **split)
{
	int i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
