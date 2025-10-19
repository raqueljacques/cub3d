/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:42:57 by rdos-san          #+#    #+#             */
/*   Updated: 2025/09/27 00:42:57 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

/* Window dimensions */
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

/* Key codes (X11) */
# define KEY_ESC   65307
# define KEY_W     119
# define KEY_A     97
# define KEY_S     115
# define KEY_D     100
# define KEY_LEFT  65361
# define KEY_RIGHT 65363

/* Map tiles */
# define TILE_WALL '1'
# define TILE_EMPTY '0'

/* Field of view helper (plane length ~ tan(FOV/2)) */
# define CAMERA_PLANE 0.66

/* Movement settings */
# define MOVE_SPEED 0.05
# define ROT_SPEED  0.03

#endif