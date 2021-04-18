#include "minirt.h"

static t_bmp_header g_bmp_header = (t_bmp_header){
	 .bitmap_signature_bytes[0] = 'B',
	 .bitmap_signature_bytes[1] = 'M',
	 .size_of_bitmap_file = 0,
	 .reserved_bytes = 0,
	 .pixel_data_offset = BMP_TOTAL_HEADER_SIZE,
	 .size_of_info_header = BMP_INFO_HEADER_SIZE,
	 .width = 0, // in pixels
	 .height = 0, // in pixels
	 .number_of_color_planes = 1, // must be 1
	 .color_depth = 32,
	 .compression_method = 0,
	 .raw_bitmap_data_size = 0, // generally ignored
	 .horizontal_resolution = 0, // in pixel per meter
	 .vertical_resolution = 0, // in pixel per meter
	 .color_table_entries = 0,
	 .important_colors = 0,
};

static char *create_filename(int file_number)
{
	const char		basename[] = "minimage_";
	const char		bmp_extension[] = ".bmp";
	char			*filename;
	char			*number;


	filename = malloc(sizeof(basename) + 10 + sizeof(bmp_extension));
	if (!filename)
		die("Malloc failed");
	number = ft_itoa(file_number);
	strcpy(filename, basename);
	strcat(filename, number);
	free(number);
	strcat(filename, bmp_extension);

	return (filename);
}

char	*get_bmp_data_from_image(char* data, size_t data_size)
{
	void	*ret;

	ret = malloc(data_size);
	if (!ret)
		die("Malloc failed");
	ft_strlcpy(ret, data, data_size);
	return (ret);

}

void	create_bmp()
{
	int				fd;
	struct s_image *image;
	size_t			data_size;
	char			*filename;
	int				i;
	void			*bmp_data;

	i = 0;
	image = env.images;
	data_size = env.res_x * env.res_y * sizeof(int);
	g_bmp_header.size_of_bitmap_file = data_size + BMP_TOTAL_HEADER_SIZE;
	g_bmp_header.raw_bitmap_data_size = data_size + BMP_TOTAL_HEADER_SIZE;
	g_bmp_header.width = env.res_x;
	g_bmp_header.height = -env.res_y;
	while (i < env.number_of_cams)
	{
		filename = create_filename(i);
		fd = open((const char*)filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		free(filename);
		if (fd < 0)
			die("Could not create bmp file\n");
		write(fd, &g_bmp_header, BMP_TOTAL_HEADER_SIZE);
		bmp_data = get_bmp_data_from_image(image->data, data_size);
		write(fd, bmp_data, data_size);
		free(bmp_data);
		close(fd);
		image = image->next;
		i++;
	}
}
