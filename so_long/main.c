#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"



typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



// void	ft_tree1(char *mlx)
// {
// 	char		*tree;
// 	static void	*img;
// 	int			pos[2];
// 	pos[0] = 5;
// 	pos[1] = 5;

// 	tree = "baum3.xpm";

// 		img = mlx_xpm_file_to_image(mlx, tree, &pos[0], &pos[1]);
// 		mlx_put_image_to_window(mlx, mlx, p, x, y);
// }

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	long long i =0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	// while(i<2000000)
	// {
	// my_mlx_pixel_put(&img, i, 5, 0x0000FF00);
	// i++;
	// }	
		int			pos[2];
	char		*tree;
		static void	*imge;
tree = "baum3.xpm";
			imge = mlx_xpm_file_to_image(mlx, tree, &pos[0], &pos[1]);
	mlx_put_image_to_window(mlx, mlx_win, imge, 0, 0);
	mlx_loop(mlx);
}