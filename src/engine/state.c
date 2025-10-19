/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacarla <student@42>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 00:00:00 by anacarla          #+#    #+#             */
/*   Updated: 2025/10/19 00:00:00 by anacarla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	g_dir_x;
static double	g_dir_y;
static double	g_plane_x;
static double	g_plane_y;

void	engine_set_dir_plane(double dir_x, double dir_y,
            double plane_x, double plane_y)
{
	g_dir_x = dir_x;
	g_dir_y = dir_y;
	g_plane_x = plane_x;
	g_plane_y = plane_y;
}

void	engine_get_dir_plane(double *dir_x, double *dir_y,
            double *plane_x, double *plane_y)
{
	if (dir_x) *dir_x = g_dir_x;
	if (dir_y) *dir_y = g_dir_y;
	if (plane_x) *plane_x = g_plane_x;
	if (plane_y) *plane_y = g_plane_y;
}
