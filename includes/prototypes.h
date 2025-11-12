/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:16:14 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/12 15:10:56 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "structs.h"

int		print_error(const char *message);
int		parse_color_rgb_to_int(const char *str);
void	free_game_data(t_game *game);
void	free_split(char **split);
int		render_scene(t_game *game);
void	cleanup_and_exit(t_game *game, int code);
int		handle_close(t_game *game);

// Parser
void	exit_error(const char *msg, t_game *game);
void	parse_and_validate(char *filename, t_game *game);
void	parse_map(int *line_index, t_game *game);
void	parse_elements(int *line_index, t_game *game);
void	validate_map_with_flood_fill(t_game *game);

// Textures
void	load_textures(t_game *game);

// Player Functions
void	player_start(t_game *game);
int		release_keys(int key, t_game *game);
int		pressing_keys(int key, t_game *game);
void	move_player(t_game *game);

char	**read_file_to_array(int fd);
#endif
