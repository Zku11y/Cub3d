#include "../../includes/cub3d.h"

void ft_init_10(t_cube *cube, t_nc *nu){
    // cube->texture2 = mlx_load_png("./Tiles_Rectangle_Grey_1.png");
    // cube->texture3 = mlx_load_png("./Concrete_02_Grey_1.png");
    cube->texture2 = nu->txtrs[SO];
    cube->texture3 = nu->txtrs[WE];
    cube->texture4 = nu->txtrs[EA];
    // cube->texture4 = mlx_load_png("./job_dude.png");
    cube->texture5 = mlx_load_png("./Monster_1.png");
    cube->texture6 = mlx_load_png("./job_app.png");
    cube->texture_died = mlx_load_png("./you_died.png");
    cube->crosshair = mlx_load_png("./crosshair_2.png");
    cube->line_girth = (int)(cube->screen_width / cube->res);
    if(cube->line_girth == 0)
        cube->line_girth = 1;
    cube->mlx = mlx_init(cube->screen_width_buff, cube->screen_height_buff, "cub3d", true);
    if(cube->mlx == NULL)
    {
        perror("mlx init error :");
        exit(EXIT_FAILURE);
    }
    cube->image = mlx_new_image(cube->mlx, cube->screen_width_buff, cube->screen_height_buff);
    if(cube->image == NULL)
    {
        mlx_terminate(cube->mlx);
        perror("image init error :");
        exit(EXIT_FAILURE);
    }
    cube->image_death = mlx_new_image(cube->mlx, cube->screen_width_buff, cube->screen_height_buff);    
}

void ft_init_11(t_cube *cube, t_nc *nu){
    if(cube->image_death == NULL)
    {
        mlx_terminate(cube->mlx);
        perror("image init error :");
        exit(EXIT_FAILURE);
    }
    mlx_image_to_window(cube->mlx, cube->image, 0, 0);
    mlx_set_mouse_pos(cube->mlx, cube->screen_width / 2, cube->screen_height / 2);    
}