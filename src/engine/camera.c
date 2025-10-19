/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacarla <student@42>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 00:00:00 by anacarla          #+#    #+#             */
/*   Updated: 2025/10/19 00:00:00 by anacarla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	compute_dir_plane(char dir_char, double *dir_x, double *dir_y,
            double *plane_x, double *plane_y)
{
	if (dir_char == 'N')
	{
		*dir_x = 0; *dir_y = -1;
		*plane_x = CAMERA_PLANE; *plane_y = 0;
	}
	else if (dir_char == 'S')
	{
		*dir_x = 0; *dir_y = 1;
		*plane_x = -CAMERA_PLANE; *plane_y = 0;
	}
	else if (dir_char == 'E')
	{
		*dir_x = 1; *dir_y = 0;
		*plane_x = 0; *plane_y = CAMERA_PLANE;
	}
	else /* 'W' or fallback */
	{
		*dir_x = -1; *dir_y = 0;
		*plane_x = 0; *plane_y = -CAMERA_PLANE;
	}
}
