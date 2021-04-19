#include "minirt.h"

static t_bmp_header g_bmp_header = (t_bmp_header){
	 .bitmap_signature_bytes[0] = 'B',
	 .bitmap_signature_bytes[1] = 'M',
	 .size_of_bitmap_file = 0,
	 .reserved_bytes = 0,
	 .pixel_data_offset = BMP_TOTAL_HEADER_SIZE,
	 .size_of_info_header = BMP_INFO_HEADER_SIZE,
	 .width = 0,
	 .height = 0,
	 .number_of_color_planes = 1,
	 .color_depth = COLOR_DEPTH,
	 .compression_method = 0,
	 .raw_bitmap_data_size = 0,
	 .horizontal_resolution = 0,
	 .vertical_resolution = 0,
	 .color_table_entries = 0,
	 .important_colors = 0,
};

static char *create_filename(int file_number)
{
	const char		basename[] = "minimage_";
	const char		bmp_extension[] = ".bmp";
	char			*filename;
	char			*number;
	int				size;


	size = sizeof(basename) + MAX_INTEGER_LEN + sizeof(bmp_extension);
	filename = malloc(size);
	if (!filename)
		die("Malloc failed");
	number = ft_itoa(file_number);
	ft_strlcpy(filename, basename, size);
	ft_strlcat(filename, number, size);
	free(number);
	ft_strlcat(filename, bmp_extension, size);

	return (filename);
}

static void	write_bmp_data(int fd, int *data)
{
	int		x;
	int		y;

	y = env.res_y - 1;
	while(y >= 0) {
		x = 0;
		while(x < env.res_x)
		{
			if((write(fd, &data[y * env.res_x + x], COLOR_DEPTH / BYTE_SZ)) < 0)
					die("Probem writing file");
			x++;
		}
		y--;
	}
}

void	create_bmp()
{
	int				fd;
	struct s_image *image;
	size_t			data_size;
	char			*filename;
	int				i;

	i = 0;
	image = env.images;
	data_size = env.res_x * env.res_y * sizeof(int);
	g_bmp_header.size_of_bitmap_file = data_size + BMP_TOTAL_HEADER_SIZE;
	g_bmp_header.width = env.res_x;
	g_bmp_header.height = env.res_y;
	while (i < env.number_of_cams)
	{
		filename = create_filename(i);
		fd = open((const char*)filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		free(filename);
		if (fd < 0)
			die("Could not create bmp file\n");
		write(fd, &g_bmp_header, BMP_TOTAL_HEADER_SIZE);
		write_bmp_data(fd, (int*)image->data);
		close(fd);
		image = image->next;
		i++;
	}
}
