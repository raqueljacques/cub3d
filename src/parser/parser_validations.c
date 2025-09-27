/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:25:44 by rdos-san          #+#    #+#             */
/*   Updated: 2025/09/27 01:25:44 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void check_file_extension(const char *filename)
{
    const char *extension = ".cub";
    size_t filename_len = ft_strlen(filename);

    if (filename_len < 4 || 
        ft_strncmp(filename + filename_len - 4, extension, 4) != 0)
    {
        print_error("Error: Invalid file extension. Expected a .cub file.");
        exit(EXIT_FAILURE);
    }
}

int validate_file(char **argv)
{
    check_file_extension(argv[1]);
    check_textures();
    check_colors();
    check_map();
}

