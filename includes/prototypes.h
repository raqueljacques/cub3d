double cast_ray_column(t_game *game, t_vec2 dir, t_vec2 plane, int screen_x, int *out_side);
void    compute_dir_plane(char dir_char, t_vec2 *dir, t_vec2 *plane);
void    render_scene(t_game *game);
void    mlx_draw_wall_column(void *mlx_ptr, void *win_ptr, int x, int start, int end, int side);
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

void    init_player_from_map(t_game *game);

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
#endif