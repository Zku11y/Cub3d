#include "../../includes/cub3d.h"

void ft_init_5(t_cube *cube, t_nc *nu){
    cube->menu.settings.mouse_sens.slider_2 = mlx_load_png("./settings_assets/slider_2.png");
    cube->menu.settings.mouse_sens.slider_start_y = 0.78 * cube->screen_height_buff;
    cube->menu.settings.mouse_sens.slider_end_y = 0.81 * cube->screen_height_buff;
    cube->menu.settings.mouse_sens.slider_start_x = 0.605 * cube->screen_width_buff;
    cube->menu.settings.mouse_sens.slider_end_x = 0.895 * cube->screen_width_buff;
    cube->menu.settings.mouse_sens.min_sens = 0.0002;
    cube->menu.settings.mouse_sens.max_sens = 0.0040;

    cube->menu.settings.resolution.res_480_glow = mlx_load_png("./settings_assets/720_480_glow.png");
    cube->menu.settings.resolution.res_720_glow = mlx_load_png("./settings_assets/1280_720_glow.png");
    cube->menu.settings.resolution.res_900_glow = mlx_load_png("./settings_assets/1600_900_glow.png");
    cube->menu.settings.resolution.res_1080_glow = mlx_load_png("./settings_assets/1920_1080_glow.png");
    if(cube->screen_height_buff == 1080)
        cube->menu.settings.resolution.texture = cube->menu.settings.resolution.res_1080_glow; 
    if(cube->screen_height_buff == 900)
        cube->menu.settings.resolution.texture = cube->menu.settings.resolution.res_900_glow; 
    if(cube->screen_height_buff == 720)
        cube->menu.settings.resolution.texture = cube->menu.settings.resolution.res_720_glow; 
    if(cube->screen_height_buff == 480)
        cube->menu.settings.resolution.texture = cube->menu.settings.resolution.res_480_glow;    
}

void ft_init_6(t_cube *cube, t_nc *nu){
    cube->menu.settings.resolution.start_x_1080 = 0.055 * cube->screen_width_buff;
    cube->menu.settings.resolution.end_x_1080 = 0.175 * cube->screen_width_buff;
    cube->menu.settings.resolution.start_x_900 = 0.245 * cube->screen_width_buff;
    cube->menu.settings.resolution.end_x_900 = 0.358 * cube->screen_width_buff;
    cube->menu.settings.resolution.start_x_720 = 0.057 * cube->screen_width_buff;
    cube->menu.settings.resolution.end_x_720 = 0.173 * cube->screen_width_buff;
    cube->menu.settings.resolution.start_x_480 = 0.265 * cube->screen_width_buff;
    cube->menu.settings.resolution.end_x_480 = 0.365 * cube->screen_width_buff;
    cube->menu.settings.resolution.start_y_1080_900 = 0.48 * cube->screen_height_buff;
    cube->menu.settings.resolution.end_y_1080_900 = 0.51 * cube->screen_height_buff;
    cube->menu.settings.resolution.start_y_720_480 = 0.59 * cube->screen_height_buff;
    cube->menu.settings.resolution.end_y_720_480 = 0.62 * cube->screen_height_buff;
    cube->menu.settings.crosshair.border = mlx_load_png("./settings_assets/border.png");
    cube->menu.settings.crosshair.color = CROSSHAIR_COLOR;
    cube->menu.settings.crosshair.start_x = 0.636 * cube->screen_width_buff;
    cube->menu.settings.crosshair.end_x = 0.865 * cube->screen_width_buff;
    cube->menu.settings.crosshair.start_y = 0.178 * cube->screen_height_buff;
    cube->menu.settings.crosshair.end_y = 0.58 * cube->screen_height_buff;
    cube->menu.state = 0;
    cube->tilt_angle = 0.0;
    cube->target_angle = 0.0;
    cube->shear_factor = tan(cube->tilt_angle * RADIANT_RATE);
    cube->tilt_addition_height = fabs(cube->shear_factor) * cube->screen_height;
    cube->tilt_addition_width = fabs(cube->shear_factor) * cube->screen_width;    
}

void ft_init_7(t_cube *cube, t_nc *nu){
    struct timeval tv;

    gettimeofday(&tv, NULL);
    cube->player.weapon.DMG = 50;
    cube->player.weapon.fire_rate = 2;
    cube->player.weapon.idle_texture = mlx_load_png("./shotgun_idle.png");
    // cube->player.weapon.idle_texture_2 = mlx_load_png("./shotgun_idle_2.png");
    cube->player.weapon.shoot_texture = mlx_load_png("./shoot_shotgun_test.png");
    cube->player.weapon.pump_texture = mlx_load_png("./pump_shotgun_test.png");
    cube->player.weapon.texture = cube->player.weapon.idle_texture;
    cube->player.weapon.pitch_increase = 1;
    cube->player.weapon.pitch_increased = 0;
    cube->player.weapon.idle_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    cube->player.weapon.idle_frame = 0;
    cube->player.weapon.move_lerp = 0;
    cube->player.weapon.pitch_changed = false;
    cube->heart.frame_1 = mlx_load_png("./blood_lvl_1.png");
    cube->heart.frame_2 = mlx_load_png("./blood_lvl_2.png");
    cube->heart.frame_3 = mlx_load_png("./blood_lvl_3.png");
    cube->heart.frame_4 = mlx_load_png("./blood_lvl_4.png");
    cube->heart.prev_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    cube->heart.frame = 0;
    cube->heart.last_angle = 0;
    cube->heart.last_pitch = 0;
    cube->heart.added_angle = 0;
}

void ft_init_8(t_cube *cube, t_nc *nu){
    cube->heart.added_pitch = 0;
    cube->heart.blur_lerp = BLUR_LERP;
    cube->heart.blood_op = 0.0;
    cube->blood_explosion.frame[0] = mlx_load_png("./blood_explosion/1_0.png");
    cube->blood_explosion.frame[1] = mlx_load_png("./blood_explosion/1_1.png");
    cube->blood_explosion.frame[2] = mlx_load_png("./blood_explosion/1_2.png");
    cube->blood_explosion.frame[3] = mlx_load_png("./blood_explosion/1_3.png");
    cube->blood_explosion.frame[4] = mlx_load_png("./blood_explosion/1_4.png");
    cube->blood_explosion.frame[5] = mlx_load_png("./blood_explosion/1_5.png");
    cube->blood_explosion.frame[6] = mlx_load_png("./blood_explosion/1_6.png");
    cube->blood_explosion.frame[7] = mlx_load_png("./blood_explosion/1_7.png");
    cube->blood_explosion.frame[8] = mlx_load_png("./blood_explosion/1_8.png");
    cube->blood_explosion.frame[9] = mlx_load_png("./blood_explosion/1_9.png");
    cube->blood_explosion.frame[10] = mlx_load_png("./blood_explosion/1_10.png");
    cube->blood_explosion.frame[11] = mlx_load_png("./blood_explosion/1_11.png");
    cube->flash.r = 1.0;
    cube->flash.g = 1.0;
    cube->flash.b = 1.0;
    cube->flash.dst_r = 1.0;
    cube->flash.dst_g = 1.0;
    cube->flash.dst_b = 1.0;
    cube->flash.flashed = false;
}

void ft_init_9(t_cube *cube, t_nc *nu){
    struct timeval tv;

    gettimeofday(&tv, NULL);
    cube->crosshair_hori_start = (t_vect2){(cube->screen_width_buff / 2) - CROSSHAIR_LEN, (cube->screen_height_buff / 2) - CROSSHAIR_GIRTH, 0, 0};
    cube->crosshair_hori_end = (t_vect2){(cube->screen_width_buff / 2) + CROSSHAIR_LEN, (cube->screen_height_buff / 2) + CROSSHAIR_GIRTH, 0, 0};
    cube->crosshair_vert_start = (t_vect2){(cube->screen_width_buff / 2) - CROSSHAIR_GIRTH, (cube->screen_height_buff / 2) - CROSSHAIR_LEN, 0, 0};
    cube->crosshair_vert_end = (t_vect2){(cube->screen_width_buff / 2) + CROSSHAIR_GIRTH, (cube->screen_height_buff / 2) + CROSSHAIR_LEN, 0, 0};
    cube->projectiles = ts_calloc(MAX_PROJECTILES + 1, sizeof(t_projectile));
    cube->prev_buffer = ts_calloc(cube->screen_height * cube->screen_width, 4);
    cube->new_buffer = ts_calloc((cube->screen_height - cube->tilt_addition_height) * (cube->screen_width - cube->tilt_addition_width), 4);
    cube->lerp_buffer = ts_calloc(cube->screen_height * cube->screen_width, 4);
    cube->mod_rate = (cube->fov * RADIANT_RATE) / cube->res;
    cube->fps = 0;
    cube->grain = true;
    cube->pitch = 0.0;
    cube->z_buffer = ts_calloc(cube->screen_width, sizeof(double));
    cube->rays = ts_calloc(cube->res + 1, sizeof(t_ray));
    cube->init_t = tv.tv_sec;
    cube->final_t = tv.tv_sec;
    cube->moving = false;
    cube->enemy = ts_calloc(ENEMY_NUM + 1, sizeof(t_enemy));
    ft_init_enemies(cube);
    cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
    cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
    // cube->texture = mlx_load_png("./s2 Concrete Squares Grey.png");
    cube->texture = nu->txtrs[NO];
}