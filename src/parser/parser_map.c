

#include "../../includes/cub3d.h"

static void	check_extra_data(int *line_index, t_game *game)
{
	char	*line;
	char	*trimmed_line;

	while (game->file_content[*line_index])
	{
		line = game->file_content[*line_index];
		trimmed_line = ft_strtrim(line, " \t\n");
		if (*trimmed_line != '\0')
		{
			free(trimmed_line);
			exit_error("Error: Extra data after map.\n", game);
		}
		free(trimmed_line);
		(*line_index)++;
	}
}

static int	find_map_start(int *line_index, t_game *game)
{
	char	*trimmed_line;
	int		start_index;

	start_index = -1;
	while (game->file_content[*line_index])
	{
		trimmed_line = ft_strtrim(game->file_content[*line_index], " \t\n");
		if (*trimmed_line != '\0')
		{
			start_index = *line_index;
			free(trimmed_line);
			break ;
		}
		free(trimmed_line);
		(*line_index)++;
	}
	if (start_index == -1)
		exit_error("Error: Map not found in file.\n", game);
	return (start_index);
}

static char	**copy_map_lines(int start, int end, t_game *game)
{
	char	**map_array;
	char	*line;
	int		height;
	int		y;
	int		len;

	height = end - start;
	map_array = ft_calloc(height + 1, sizeof(char *));
	if (!map_array)
		exit_error("Error: Malloc failed for map array.\n", game);
	y = 0;
	while (y < height)
	{
		line = game->file_content[start + y];
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			map_array[y] = ft_substr(line, 0, len - 1);
		else
			map_array[y] = ft_strdup(line);
		if (!map_array[y])
			exit_error("Error: Malloc failed for map line.\n", game);
		y++;
	}
	return (map_array);
}

void	parse_map(int *line_index, t_game *game)
{
	char *trimmed_line;
	int start_index;
	int end_index;

	start_index = find_map_start(line_index, game);
	end_index = start_index;
	while (game->file_content[end_index])
	{
		trimmed_line = ft_strtrim(game->file_content[end_index], " \t\n");
		if (*trimmed_line == '\0')
		{
			free(trimmed_line);
			break ;
		}
		free(trimmed_line);
		end_index++;
	}
	*line_index = end_index;
	game->map = copy_map_lines(start_index, end_index, game);
	check_extra_data(line_index, game);
}
