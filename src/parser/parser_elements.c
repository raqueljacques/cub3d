/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:53:37 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/16 08:29:14 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	process_element_line(char *line, t_game *game);
static void	assign_and_validate_texture(char **dest, char *path, t_game *game);
static int	parse_color_rgb_to_int(const char *str);

void	parse_textures_and_colors(int fd, t_game *game)
{
	char	*line;
	char	*trimmed_line;
	int		count;

	count = 0;
	while (count < 6 && (line = get_next_line(fd)))
	{
		trimmed_line = ft_strtrim(line, " \t\n");
		if (*trimmed_line == '\0')
		{
			free(trimmed_line);
			free(line);
			continue ;
		}
		free(trimmed_line);
		process_element_line(line, game);
		free(line);
		count++;
	}
	if (count != 6 || game->floor_color == -1 || game->ceiling_color == -1)
	{
		print_error("Error: Missing or invalid map elements.\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
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
	{
		print_error("Error: Invalid element format or identifier.\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
}

static void	assign_and_validate_texture(char **dest, char *path, t_game *game)
{
	int		fd;
	char	*trimmed_path;

	trimmed_path = ft_strtrim(path, " \n\t");
	if (!trimmed_path || *trimmed_path == '\0')
	{
		print_error("Error: Texture path is missing.\n");
		free(trimmed_path);
		exit(EXIT_FAILURE);
	}
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

static int	parse_color_rgb_to_int(const char *str)
{
	char	**rgb_values;
	int		color;
	int		i;
	int		value;
	char	*trimmed_value;

	rgb_values = ft_split(str, ',');
	i = 0;
	while (rgb_values && rgb_values[i])
		i++;
	if (i != 3)
	{
		free_split(rgb_values);
		return (-1);
	}
	i = 0;
	color = 0;
	while (i < 3)
	{
		trimmed_value = ft_strtrim(rgb_values[i], " \t\n");
		value = ft_atoi(trimmed_value);
		if (*trimmed_value == '\0' || value < 0 || value > 255)
		{
			free(trimmed_value);
			free_split(rgb_values);
			return (-1);
		}
		free(trimmed_value);
		color = (color << 8) | value;
		i++;
	}
	free_split(rgb_values);
	return (color);
}