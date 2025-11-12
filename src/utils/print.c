/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:05:06 by rdos-san          #+#    #+#             */
/*   Updated: 2025/10/22 15:08:43 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	print_error(const char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	return (1);
}

void	exit_error(const char *msg, t_game *game)
{
	print_error(msg);
	if (game)
		free_game_data(game);
	exit(EXIT_FAILURE);
}
