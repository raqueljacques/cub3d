/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:25:44 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/04 17:02:29 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_file_extension(const char *filename);

void	parse_and_validate(char *filename, t_game *game)
{
	int	fd;

	check_file_extension(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Error: Could not open the map file.\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(game, sizeof(t_game));
	parse_textures_and_colors(fd, game);
	parse_map(fd, game);
	validate_map(game);
	close(fd);
}

static void	check_file_extension(const char *filename)
{
	const char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
	{
		print_error("Error: Invalid file extension. Expected a .cub file.\n");
		exit(EXIT_FAILURE);
	}
}