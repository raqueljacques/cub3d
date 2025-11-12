/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:16:07 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/12 15:10:13 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	char	**file_content;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		map_width;
	int		map_height;
	double	player_x;
	double	player_y;
	char	player_dir;
}			t_game;

#endif