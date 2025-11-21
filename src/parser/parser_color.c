/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:58:00 by rdos-san          #+#    #+#             */
/*   Updated: 2025/11/21 14:16:07 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	validate_rgb_part(char *part, int *value)
{
	char	*trimmed;
	int		i;

	trimmed = ft_strtrim(part, " \t\n");
	if (!trimmed || *trimmed == '\0')
		return (free(trimmed), 0);
	i = 0;
	while (trimmed[i])
	{
		if (!ft_isdigit(trimmed[i]))
		{
			free(trimmed);
			return (0);
		}
		i++;
	}
	*value = ft_atoi(trimmed);
	free(trimmed);
	if (*value < 0 || *value > 255)
		return (0);
	return (1);
}

static int	build_color_from_rgb(char **rgb_values)
{
	int	color;
	int	value;
	int	i;

	color = 0;
	i = 0;
	while (i < 3)
	{
		if (!validate_rgb_part(rgb_values[i], &value))
			return (-1);
		color = (color << 8) | value;
		i++;
	}
	return (color);
}

int	parse_color_rgb_to_int(const char *str)
{
	char **rgb_values;
	int color;
	int count;

	rgb_values = ft_split(str, ',');
	if (!rgb_values)
		return (-1);
	count = 0;
	while (rgb_values[count])
		count++;
	if (count != 3)
		return (free_split(rgb_values), -1);
	color = build_color_from_rgb(rgb_values);
	free_split(rgb_values);
	return (color);
}