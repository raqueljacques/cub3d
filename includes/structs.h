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

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	turn_left;
	bool	turn_right;
}				t_player;

typedef struct s_texture
{
	char	*path;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}				t_texture;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	t_player	player;
	t_texture	north_texture;
	t_texture	south_texture;
	t_texture	west_texture;
	t_texture	east_texture;
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
