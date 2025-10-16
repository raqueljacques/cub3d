/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:11:16 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/16 16:06:51 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_extra_data(int fd, t_game *game);
static char	*read_map_buffer(int fd);
static void	process_map_line(char **map_buffer, char *line, int *started);

void	parse_map(int fd, t_game *game)
{
	char	*map_buffer;

	map_buffer = read_map_buffer(fd);
	if (*map_buffer == '\0')
	{
		print_error("Error: Map not found in the file.\n");
		exit(EXIT_FAILURE);
	}
	game->map = ft_split(map_buffer, '\n');
	free(map_buffer);
	check_extra_data(fd, game);
}

static char	*read_map_buffer(int fd)
{
	char	*line;
	char	*map_buffer;
	int		started;

	started = 0;
	map_buffer = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		if ((!started && *line == '\n') || (started && *line == '\n'))
		{
			free(line);
			if (started)
				break ;
			line = get_next_line(fd);
			continue ;
		}
		process_map_line(&map_buffer, line, &started);
		free(line);
		line = get_next_line(fd);
	}
	return (map_buffer);
}

static void	process_map_line(char **map_buffer, char *line, int *started)
{
	char	*tmp;

	if (!(*started) && *line == '\n')
		return ;
	if (*started && *line == '\n')
		return ;
	*started = 1;
	tmp = ft_strjoin(*map_buffer, line);
	free(*map_buffer);
	*map_buffer = tmp;
}

static void	check_extra_data(int fd, t_game *game)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		if (line[i] != '\0')
		{
			free(line);
			free_game_data(game);
			print_error("Error: Extra data after map.\n");
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
}
