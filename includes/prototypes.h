/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:16:14 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/04 17:33:37 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "structs.h"

// Utils
int		print_error(const char *message);
void	free_game_data(t_game *game);
void	free_split(char **split);

// Parser
void	parse_and_validate(char *filename, t_game *game);

// Parser Map
void	parse_map(int fd, t_game *game);
void	validate_map(t_game *game);

// Parser Elements
void	parse_textures_and_colors(int fd, t_game *game);

// Flood Fill Validation
void	validate_map_with_flood_fill(t_game *game);

// Engine - Camera/Direction
void	compute_dir_plane(char dir_char, double *dir_x, double *dir_y,
			double *plane_x, double *plane_y);

// Engine - Raycasting (no rendering)
double	cast_ray_column(const t_game *game,
			double dir_x, double dir_y,
			double plane_x, double plane_y,
			int screen_x, int *out_side);

// Engine - Shared state (dir/plane)
void	engine_set_dir_plane(double dir_x, double dir_y,
			double plane_x, double plane_y);
void	engine_get_dir_plane(double *dir_x, double *dir_y,
			double *plane_x, double *plane_y);
#endif