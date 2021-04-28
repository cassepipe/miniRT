/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:26:29 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/28 17:38:40 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		check_args(int argc, char *argv[])
{
	if (argc != 2)
	{
		if (argc == 3)
		{
			if (!ft_strncmp(argv[2], "--save", sizeof("--save")))
				g_env.bmp_mode = true;
			else if (argv[2][0] == '-')
				die("`--save` is the only valid option");
			else
				die("Too many arguments");
		}
		else if (argc == 1)
			die("You must provide an .rt file");
		else
			die("Too many arguments");
	}
}

void		check_rt_extension(char *filename)
{
	size_t len;

	len = ft_strlen(filename);
	if (filename[len - 1] != 't'
		|| filename[len - 2] != 'r'
		|| filename[len - 3] != '.')
		die("You must provide a .rt file");
}
