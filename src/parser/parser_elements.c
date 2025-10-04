/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:53:37 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/04 18:17:38 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	process_element_line_tokens(char **tokens, t_game *game);
static void	assign_and_validate_texture(char **dest, char *path, t_game *game);
static int	parse_color_rgb_to_int(const char *str);

void	parse_textures_and_colors(int fd, t_game *game)
{
	char	*line;
	char	**tokens;
	int		count;

	count = 0;
	while (count < 6 && (line = get_next_line(fd)))
	{
		if (*line == '\n' || *line == '\0')
		{
			free(line);
			continue ;
		}
		tokens = ft_split(line, ' ');
		free(line);
		process_element_line_tokens(tokens, game);
		free_split(tokens);
		count++;
	}
	if (count != 6 || game->floor_color == -1 || game->ceiling_color == -1)
	{
		print_error("Error: Missing or invalid map elements.\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
}

static void	process_element_line_tokens(char **tokens, t_game *game)
{
	// Regras:
	// 1. Precisa existir os tokens
	// 2. tokens[0] e tokens[1] não podem ser nulos pois é o identificador e o valor
	// 3. tokens[2] deve ser nulo, pois não pode existir um terceiro token
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
	{
		print_error("Error: Invalid element format.\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(tokens[0], "NO", 3) == 0)
		assign_and_validate_texture(&game->north_texture, tokens[1], game);
	else if (ft_strncmp(tokens[0], "SO", 3) == 0)
		assign_and_validate_texture(&game->south_texture, tokens[1], game);
	else if (ft_strncmp(tokens[0], "WE", 3) == 0)
		assign_and_validate_texture(&game->west_texture, tokens[1], game);
	else if (ft_strncmp(tokens[0], "EA", 3) == 0)
		assign_and_validate_texture(&game->east_texture, tokens[1], game);
	else if (ft_strncmp(tokens[0], "F", 2) == 0)
		game->floor_color = parse_color_rgb_to_int(tokens[1]);
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
		game->ceiling_color = parse_color_rgb_to_int(tokens[1]);
	else
	{
		print_error("Error: Unknown identifier found.\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
}

static void	assign_and_validate_texture(char **dest, char *path, t_game *game)
{
	int		fd;
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("Diretório de trabalho atual: %s\n", cwd);
	}
	else
	{
		perror("Erro ao obter diretório de trabalho");
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		print_error("Error: Cannot open texture file: ");
		print_error(path);
		print_error("\n");
		free_game_data(game);
		exit(EXIT_FAILURE);
	}
	close(fd);
	*dest = ft_strdup(path);
}

static int	parse_color_rgb_to_int(const char *str)
{
	char **rgb_values;
	int color;
	int i;
	int value;

	rgb_values = ft_split(str, ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2]
		|| rgb_values[3])
		return (-1);
	i = 0;
	color = 0;
	while (i < 3)
	{
		value = ft_atoi(rgb_values[i]);
		if (value < 0 || value > 255)
		{
			free_split(rgb_values);
			return (-1);
		}
		color = (color << 8) | value;
		free(rgb_values[i++]);
	}
	free(rgb_values);
	return (color);
}