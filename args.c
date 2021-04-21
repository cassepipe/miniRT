/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:50 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/21 15:06:32 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		check_args(int argc, char *argv[])
{
	if (argc != 2)
	{
		if (argc == 3)
		{
			if (!strcmp(argv[2], "--save"))
				env.bmp_mode = true;
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
		|| filename[len - 3] != '.' )
		die("You must provide a .rt file");
}
