/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:28 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/27 12:08:55 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

# include <stdint.h>

struct __attribute__((__packed__))	s_bmp_header {
	char			bitmap_signature_bytes[2];
	uint32_t		size_of_bitmap_file;
	const uint32_t	reserved_bytes;
	const uint32_t	pixel_data_offset;
	const uint32_t	size_of_info_header;
	int32_t			width;
	int32_t			height;
	const uint16_t	number_of_color_planes;
	const uint16_t	color_depth;
	const uint32_t	compression_method;
	const uint32_t	raw_bitmap_data_size;
	const int32_t	horizontal_resolution;
	const int32_t	vertical_resolution;
	const uint32_t	color_table_entries;
	const uint32_t	important_colors;
};

typedef struct s_bmp_header	t_bmp_header;

#endif
