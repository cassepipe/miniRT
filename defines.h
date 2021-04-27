/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:27 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/27 11:29:31 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define EPSILON 					0.00001
# define ESC						0xff1b
# define SPACE						0x20
# define TAB						0xff09
# define DESTROY_NOTIFY				17
# define BMP_TOTAL_HEADER_SIZE		54
# define BMP_HEADER_SIZE			14
# define BMP_INFO_HEADER_SIZE		40
# define MAX_INTEGER_LEN			10
# define COLOR_DEPTH				32
# define BYTE						8

/*
**  Do no set out of range values !
*/

# define DEFAULT_AMBIENT_LIGHT_INTENSITY 		1

#endif
