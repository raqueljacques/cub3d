/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:05:06 by rdos-san          #+#    #+#             */
/*   Updated: 2025/09/27 01:05:06 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	print_error(const char *message)
{
    const char *completed_message = message + "\n";

    ft_putstr_fd(completed_message, STDERR_FILENO);
    return (1);
}