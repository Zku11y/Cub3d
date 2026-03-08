#include "../../includes/cub3d.h"

void ft_clean(t_cube *cube, t_nc *nu)
{
	cube->mlx = mlx_init(cube->screen_width_buff, cube->screen_height_buff, "cub3d", true);
	cube->image = mlx_new_image(cube->mlx, cube->screen_width_buff, cube->screen_height_buff);
	cube->image_death = mlx_new_image(cube->mlx, cube->screen_width_buff, cube->screen_height_buff);
	mlx_delete_texture(cube->menu.title);
	mlx_delete_texture(cube->menu.settings.background);
	mlx_delete_texture(cube->menu.settings.fov.bar_1);
	mlx_delete_texture(cube->menu.settings.bar_2);
	mlx_delete_texture(cube->menu.settings.fov.slider_1);
	mlx_delete_texture(cube->menu.settings.slider_2);
	mlx_delete_texture(cube->menu.settings.ups.x1_glow);
	mlx_delete_texture(cube->menu.settings.ups.x2_glow);
	mlx_delete_texture(cube->menu.settings.ups.x3_glow);
	mlx_delete_texture(cube->menu.settings.ups.x4_glow);
	mlx_delete_texture(cube->menu.settings.ups.x5_glow);
	mlx_delete_texture(cube->menu.settings.ups.x6_glow);
	mlx_delete_texture(cube->menu.settings.ups.x7_glow);
	mlx_delete_texture(cube->menu.settings.ups.x8_glow);
	mlx_delete_texture(cube->menu.settings.mouse_sens.slider_2);
	mlx_delete_texture(cube->menu.settings.res._480);
	mlx_delete_texture(cube->menu.settings.res._720);
	mlx_delete_texture(cube->menu.settings.res._900);
	mlx_delete_texture(cube->menu.settings.res._1080);
	mlx_delete_texture(cube->menu.settings.crosshair.border);
	mlx_delete_texture(cube->player.weapon.idle_texture);
	mlx_delete_texture(cube->player.weapon.shoot_texture);
	mlx_delete_texture(cube->player.weapon.pump_texture);
	mlx_delete_texture(cube->heart.frame_1);
	mlx_delete_texture(cube->heart.frame_2);
	mlx_delete_texture(cube->heart.frame_3);
	mlx_delete_texture(cube->heart.frame_4);
	mlx_delete_texture(cube->blood.frame[0]);
	mlx_delete_texture(cube->blood.frame[1]);
	mlx_delete_texture(cube->blood.frame[2]);
	mlx_delete_texture(cube->blood.frame[3]);
	mlx_delete_texture(cube->blood.frame[4]);
	mlx_delete_texture(cube->blood.frame[5]);
	mlx_delete_texture(cube->blood.frame[6]);
	mlx_delete_texture(cube->blood.frame[7]);
	mlx_delete_texture(cube->blood.frame[8]);
	mlx_delete_texture(cube->blood.frame[9]);
	mlx_delete_texture(cube->blood.frame[10]);
	mlx_delete_texture(cube->blood.frame[11]);
	mlx_delete_texture(cube->texture5);
	mlx_delete_texture(cube->texture6);
	mlx_delete_texture(cube->texture_died);
	mlx_delete_texture(cube->crosshair);
	mlx_delete_texture(cube->enemy[0].health);
	if(cube->lerp_buffer)
		free(cube->lerp_buffer);
	if(cube->z_buffer)
		free(cube->z_buffer);
	if(cube->rays)
		free(cube->rays);
	if(cube->enemy)
		free(cube->enemy);
	if(cube->projectiles)
		free(cube->projectiles);
	if(cube->prev_buffer)
		free(cube->prev_buffer);
	if(cube->new_buffer)
		free(cube->new_buffer);

	if(cube->map){
		int i = 0;
		while(cube->map[i]){
			free(cube->map[i]);
			i++;
		}
		free(cube->map);
	}
}