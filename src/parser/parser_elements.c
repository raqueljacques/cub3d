/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:53:37 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/16 17:49:52 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	process_element_line(char *line, t_game *game);
static void	assign_and_validate_texture(char **dest, char *path, t_game *game);

void	parse_elements(int fd, t_game *game)
{
	char	*line;
	char	*trimmed_line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while ((count < 6) && line)
	{
		trimmed_line = ft_strtrim(line, " \t\n");
		if (*trimmed_line == '\0')
		{
			free(trimmed_line);
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		free(trimmed_line);
		process_element_line(line, game);
		free(line);
		line = get_next_line(fd);
		count++;
	}
	if (count != 6 || game->floor_color == -1 || game->ceiling_color == -1)
		exit_error("Error: Missing or invalid map elements.\n", game);
}

static void	process_element_line(char *line, t_game *game)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		assign_and_validate_texture(&game->north_texture, line + 3, game);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		assign_and_validate_texture(&game->south_texture, line + 3, game);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		assign_and_validate_texture(&game->west_texture, line + 3, game);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		assign_and_validate_texture(&game->east_texture, line + 3, game);
	else if (ft_strncmp(line, "F ", 2) == 0)
		game->floor_color = parse_color_rgb_to_int(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->ceiling_color = parse_color_rgb_to_int(line + 2);
	else
		exit_error("Error: Invalid element format or identifier.\n", game);
}

static void	assign_and_validate_texture(char **dest, char *path, t_game *game)
{
	int		fd;
	char	*trimmed_path;

	if (*dest != NULL)
		exit_error("Error: Duplicate texture detected.\n", game);
	trimmed_path = ft_strtrim(path, " \n\t");
	if (!trimmed_path || *trimmed_path == '\0')
		exit_error("Error: Texture path is missing.\n", game);
	fd = open(trimmed_path, O_RDONLY);
	if (fd < 0)
	{
		print_error("Error: Cannot open texture file: ");
		print_error(trimmed_path);
		print_error("\n");
		free(trimmed_path);
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
	close(fd);
	*dest = ft_strdup(trimmed_path);
	free(trimmed_path);
}
