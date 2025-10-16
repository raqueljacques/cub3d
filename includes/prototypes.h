/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:16:14 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/16 17:54:06 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "structs.h"

int		print_error(const char *message);
int	parse_color_rgb_to_int(const char *str);
void	free_game_data(t_game *game);
void	free_split(char **split);
void	exit_with_error(const char *msg, t_game *game);
void	parse_and_validate(char *filename, t_game *game);
void	parse_map(int fd, t_game *game);
void	parse_elements(int fd, t_game *game);
void	validate_map_with_flood_fill(t_game *game);
#endif
