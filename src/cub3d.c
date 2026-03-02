/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:13:24 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/02 05:16:15 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # define MINIAUDIO_IMPLEMENTATION
#include "../includes/cub3d.h"

void clear_image(t_cube *cube)
{
    int buffer_size = cube->screen_height * cube->screen_width * 4;
    ft_memset(cube->image->pixels, 0, buffer_size);
}

unsigned long ft_rand(unsigned long *seed){
    *seed = (*seed * 1103515245 + 12345) & 0x7fffffff;
    return (*seed);
}

void ft_rectangle(t_cube *cube, t_vect2 start_cords, t_vect2 end_cords, int color)
{
    uint32_t *prev = (uint32_t *)cube->image->pixels;
    int start_temp;
    int start_x = (int)(start_cords.x);
    int start_y = (int)(start_cords.y);
    int end_x = (int)(end_cords.x);
    int end_y = (int)(end_cords.y);

    start_temp = start_x;
    while(start_y < end_y)
    {
        start_x = start_temp;
        while(start_x < end_x)
        {
            prev[(start_y * cube->screen_width_buff) + (start_x)] = color;
            // mlx_put_pixel(cube->image, start_x, start_y, color);
            start_x++;
        }
        start_y++;
    }
}

void ft_angle_limit(double *angle)
{
    if(*angle < 0)
        *angle = (2 * PI) + *angle;
    else if(*angle > (PI * 2))
        *angle = *angle - (2 * PI);
}

uint8_t ft_lerp_pixels(uint8_t new, uint8_t old, double lerp_rate){
    return (new * lerp_rate) + (old * (1.0 - lerp_rate));
}

double ft_lerp_speed(double dst, double current){
    return (dst * SPEED_LERP) + (current * (1.0 - SPEED_LERP));
}

double ft_lerp_tilt(double dst, double current){
    return (dst * TILT_LERP) + (current * (1.0 - TILT_LERP));
}

double ft_lerp_fov(double dst, double current, double lerp_rate){
    return (dst * lerp_rate) + (current * (1.0 - lerp_rate));
}

double ft_lerp_move(double dst, double current, double lerp_rate){
    return (current * lerp_rate) + (dst * (1.0 - lerp_rate));
}


void draw_player(t_cube *cube)
{
    int y;
    int x;
    int offset;

    offset = 3;
    if(cube->player.x < offset)
        cube->player.x = offset;
    else if(cube->player.x > cube->screen_width)
        cube->player.x = cube->screen_width - offset;
    if(cube->player.y < offset)
        cube->player.y = offset;
    else if(cube->player.y > cube->screen_height)
        cube->player.y = cube->screen_height - offset;
    x = cube->player.x - offset;
    while(x < (cube->player.x + offset))
    {
        y = cube->player.y - offset;
        while(y < (cube->player.y + offset))
        {
            mlx_put_pixel(cube->image, x, y, 0xff1100ff);
            y++;
        }
        x++;
    }
}

void grid_line(t_cube *cube, int start, int finish, int cst, bool axis_x)
{
    int i;

    i = start;
    while(i < finish)
    {
        if(axis_x)
            mlx_put_pixel(cube->image, i, cst, 0xffffffff);
        else
            mlx_put_pixel(cube->image, cst, i, 0xffffffff);
        i++;
    }
}

void draw_grid(t_cube *cube)
{
    int y = 0;
    int x = 0;

    while(y < MAP_Y)
    {
        x = 0;
        while(x < MAP_X)
        {
            if(cube->map[y][x] == 1)
            {
                if(y == 0 || cube->map[y - 1][x] == 0)
                    grid_line(cube, x * GRID_SIZE, (x + 1) * GRID_SIZE, y * GRID_SIZE, true);
                if(y == MAP_Y - 1 || cube->map[y + 1][x] == 0)
                    grid_line(cube, x * GRID_SIZE, (x + 1) * GRID_SIZE, (y + 1) * GRID_SIZE, true);
                if(x == 0 || cube->map[y][x - 1] == 0)
                    grid_line(cube, y * GRID_SIZE, (y + 1) * GRID_SIZE, x * GRID_SIZE, false);
                if(x == MAP_X - 1 || cube->map[y][x + 1] == 0)
                    grid_line(cube, y * GRID_SIZE, (y + 1) * GRID_SIZE, (x + 1) * GRID_SIZE, false);
            }
            x++;
        }
        y++;
    }
}

void ft_mouvement_limits(t_cube *cube)
{
    // printf("grid cords : (%d, %d), cords : (%d, %d)\n", cube->player.grid_x, cube->player.grid_y, cube->player.x, cube->player.y);
    if(cube->map[cube->player.grid_y][cube->player.grid_x - 1] == 1)
    {
        if(cube->player.x <= (GRID_SIZE * cube->player.grid_x) + WALL_DST)
            cube->player.x = (GRID_SIZE * cube->player.grid_x) + WALL_DST;
    }
    if(cube->map[cube->player.grid_y][cube->player.grid_x + 1] == 1)
    {
        if(cube->player.x >= (GRID_SIZE * (cube->player.grid_x + 1)) - WALL_DST)
            cube->player.x = (GRID_SIZE * (cube->player.grid_x + 1)) - WALL_DST;
    }
    if(cube->map[cube->player.grid_y - 1][cube->player.grid_x] == 1)
    {
        if(cube->player.y <= (GRID_SIZE * cube->player.grid_y) + WALL_DST)
            cube->player.y = (GRID_SIZE * cube->player.grid_y) + WALL_DST;
    }
    if(cube->map[cube->player.grid_y + 1][cube->player.grid_x] == 1)
    {
        if(cube->player.y >= (GRID_SIZE * (cube->player.grid_y + 1)) - WALL_DST)
            cube->player.y = (GRID_SIZE * (cube->player.grid_y + 1)) - WALL_DST;
    }
}

void ft_turn(t_cube *cube)
{
    int mouse_x;
    int mouse_y;
    static int frames = 5;

    mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
    mouse_x = mouse_x - (cube->screen_width / 2);
    mouse_y = mouse_y - (cube->screen_height / 2);
    cube->player.angle += mouse_x * (cube->mouse_sens * 100) / (((double)cube->screen_height / 100) * (cube->menu.settings.fov.max_fov - cube->fov + cube->menu.settings.fov.min_fov));
    // cube->player.angle += mouse_x * (cube->mouse_sens);
    if (frames > 0)
        frames--;
    else
        cube->pitch += (-1 * mouse_y) * ((cube->mouse_sens * 100));
    if(cube->pitch > cube->pitch_max)
        cube->pitch = cube->pitch_max;
    if(cube->pitch < -cube->pitch_max)
        cube->pitch = -cube->pitch_max;
    mlx_set_mouse_pos(cube->mlx, cube->screen_width / 2, cube->screen_height / 2);
}

void ft_mouvement(t_cube *cube)
{
    ft_angle_limit(&cube->player.angle);
    ft_turn(cube);
    double max_cos_speed = cos(cube->player.angle) * PLAYER_SPEED * cube->mlx->delta_time;
    double max_sin_speed = sin(cube->player.angle) * PLAYER_SPEED * cube->mlx->delta_time;
    double dst_speed_LR_X = 0.0;
    double dst_speed_LR_Y = 0.0;
    double dst_speed_FB_X = 0.0;
    double dst_speed_FB_Y = 0.0;
    double target_angle = 0.0;

    if(mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT) && cube->player.delay == false){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("left mouse click pressed!\n");
    cube->player.delay = true;
    cube->player.attacked = true;
    cube->player.atk_time = tv.tv_sec;
}

    // printf("attacked : %d, delay : %d\n", cube->player.attacked, cube->player.delay);

    if(mlx_is_key_down(cube->mlx, MLX_KEY_D))
    {
        dst_speed_LR_X = -1 * max_sin_speed;
        dst_speed_LR_Y = max_cos_speed;
        target_angle = TILT_ANGLE;
    }
    else if(mlx_is_key_down(cube->mlx, MLX_KEY_A))
    {
        dst_speed_LR_X = max_sin_speed;
        dst_speed_LR_Y = -1 * max_cos_speed;
        target_angle = -TILT_ANGLE;
    }
    if(mlx_is_key_down(cube->mlx, MLX_KEY_W))
    {
        cube->player.weapon.move_lerp = ft_lerp_move(-cube->move_increase, cube->player.weapon.move_lerp, RECOIL_LERP);
        dst_speed_FB_X = max_cos_speed;
        dst_speed_FB_Y = max_sin_speed;
    }
    else if(mlx_is_key_down(cube->mlx, MLX_KEY_S))
    {
        cube->player.weapon.move_lerp = ft_lerp_move(cube->move_increase, cube->player.weapon.move_lerp, RECOIL_LERP);
        dst_speed_FB_X = -1 * max_cos_speed;
        dst_speed_FB_Y = -1 * max_sin_speed;
    }
    else{
        cube->player.weapon.move_lerp = ft_lerp_move(0, cube->player.weapon.move_lerp, RECOIL_LERP);
    }

    cube->tilt_angle = ft_lerp_tilt(target_angle, cube->tilt_angle);
    cube->shear_factor = tan(cube->tilt_angle * RADIANT_RATE);
    cube->tilt_addition_height = fabs(cube->shear_factor) * cube->screen_height;
    cube->tilt_addition_width = fabs(cube->shear_factor) * cube->screen_width;
    cube->player.current_speed_FB_X = ft_lerp_speed(dst_speed_FB_X, cube->player.current_speed_FB_X);
    cube->player.current_speed_FB_Y = ft_lerp_speed(dst_speed_FB_Y, cube->player.current_speed_FB_Y);
    cube->player.current_speed_LR_X = ft_lerp_speed(dst_speed_LR_X, cube->player.current_speed_LR_X);
    cube->player.current_speed_LR_Y = ft_lerp_speed(dst_speed_LR_Y, cube->player.current_speed_LR_Y);
    cube->player.x += cube->player.current_speed_FB_X + cube->player.current_speed_LR_X;
    cube->player.y += cube->player.current_speed_FB_Y + cube->player.current_speed_LR_Y;
    ft_mouvement_limits(cube);
    cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
    cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
}

void ft_draw_line(t_cube *cube, t_vect2 start, t_vect2 finish, int color)
{
    t_vect2 add;
    t_vect2 mod;

    ft_limit_cords(&start);
    ft_limit_cords(&finish);
    mod.x = finish.x - start.x; // -GRID_SIZE
    mod.y = finish.y - start.y; // -100
    if(fabs(mod.x) >= fabs(mod.y))
    {
        add.x = mod.x / fabs(mod.x);
        add.y = mod.y / fabs(mod.x);
    }
    else
    {
        add.x = mod.x / fabs(mod.y); // -0.5
        add.y = mod.y / fabs(mod.y); // -1
    }
    while (fabs(start.x - finish.x) > 0.5 || fabs(start.y - finish.y) > 0.5)
    {
        mlx_put_pixel(cube->image, (int)round(start.x), (int)round(start.y), color);
        start.x += add.x;
        start.y += add.y;
    }
}

t_vect2 calc_length(t_cube *cube, t_vect2 hori, t_vect2 vert, t_ray *ray)
{
    double len_hori;
    double len_vert;

    // len_hori = (fabs(hori.x - cube->player.x) / cos(ray->angle));
    // len_vert = (fabs(vert.y - cube->player.y) / sin(ray->angle));
    len_hori = (fabs(hori.y - cube->player.y) / sin(ray->angle));
    len_vert = (fabs(vert.x - cube->player.x) / cos(ray->angle));
    // printf("len_hori (%lf, %lf) == %lf, len_vert (%lf, %lf) == %lf\n", hori.x, hori.y, len_hori, vert.x, vert.y, len_vert);
    if(len_hori < len_vert)
    {
        ray->length = len_hori;
        if(ray->y_dir == UP)
            // ray->normal_dst = (hori.x / GRID_SIZE) - hori.grid_x;
            ray->normal_dst = fmod(hori.x, GRID_SIZE) / GRID_SIZE;
        else
            // ray->normal_dst = 1 - ((hori.x / GRID_SIZE) - hori.grid_x);
            ray->normal_dst = 1 - (fmod(hori.x, GRID_SIZE) / GRID_SIZE);
        return (hori);
    }
    ray->length = len_vert;
    if(ray->x_dir == RIGHT)
        // ray->normal_dst = (vert.y / GRID_SIZE) - vert.grid_y;
        ray->normal_dst = fmod(vert.y, GRID_SIZE) / GRID_SIZE;
    else
        // ray->normal_dst = 1 - ((vert.y / GRID_SIZE) - vert.grid_y);
        ray->normal_dst = 1 - (fmod(vert.y, GRID_SIZE) / GRID_SIZE);
    return (vert);
}

void ft_ray_init(t_cube *cube, t_ray *ray, double angle)
{
    ray->start.x = cube->player.x;
    ray->start.y = cube->player.y;
    ray->angle = angle;
    if(ray->angle >= PI && ray->angle <= 2 * PI)
        ray->y_dir = UP;
    else
        ray->y_dir = DOWN;
    if((ray->angle >= 0.5 * PI) && (ray->angle <= 1.5 * PI))
        ray->x_dir = LEFT;
    else
        ray->x_dir = RIGHT;
    if(ray->y_dir == UP && ray->x_dir == RIGHT)
        ray->angle = (2 * PI) - angle;
    else if(ray->y_dir == UP && ray->x_dir == LEFT)
        ray->angle = angle - PI;
    else if(ray->y_dir == DOWN && ray->x_dir == LEFT)
        ray->angle = PI - angle;
    t_vect2 hori = hori_first_point(cube, ray);
    t_vect2 vert = vert_first_point(cube, ray);
    ray->end = calc_length(cube, hori, vert, ray);
}

void ft_draw_rays(t_cube *cube)
{
    double DirX = cos(cube->player.angle);
    double DirY = sin(cube->player.angle);
    double PlaneX = -DirY * cube->half_fov_rad;
    double PlaneY =  DirX * cube->half_fov_rad;

    for (int i = 0; i < cube->res; i++)
    {
        double cameraX = 2.0 * i / (double)cube->res - 1.0;

        double rayDirX = DirX + PlaneX * cameraX;
        double rayDirY = DirY + PlaneY * cameraX;

        double rayAngle = atan2(rayDirY, rayDirX);

        if (rayAngle < 0)
            rayAngle += 2 * PI;
        else if (rayAngle > 2 * PI)
            rayAngle -= 2 * PI;

        cube->rays[i].real_angle = rayAngle;
        ft_ray_init(cube, &(cube->rays[i]), rayAngle);
    }
}

// void ft_draw_rays(t_cube *cube)
// {
//     double start_angle;
//     int i;

//     i = 0;
//     cube->min_length = 99999999;ft_ene
//     start_angle = cube->player.angle - ((FOV / 2) * RADIANT_RATE);
//     while(i < cube->res)
//     {
//         if(start_angle < 0)
//             start_angle = (2 * PI) + start_angle;
//         else if(start_angle > (PI * 2))
//             start_angle = start_angle - (2 * PI);
//         // printf("start angle : %lf\n", start_angle);
//         cube->rays[i].real_angle = start_angle;
//         ft_ray_init(cube, &(cube->rays[i]), start_angle);
//         if(cube->rays[i].length < cube->min_length) cube->min_length = cube->rays[i].length;
//         // ft_draw_line(cube, cube->rays[i].start, cube->rays[i].end, 0xfff700ff);
//         i++;
//         start_angle += cube->mod_rate;
//     }
// }

bool check_screen_limits(t_cube *cube, t_vect2 len)
{
    if(len.x >= cube->screen_width)
        return true;
    else if(len.x < 0)
        return true;
    if(len.y >= cube->screen_height)
        return true;
    else if(len.y < 0)
        return true;
    return false;
}

void set_screen_limits(t_cube *cube, t_vect2 *len)
{
    if(len->x > cube->screen_width)
        len->x = cube->screen_width;
    else if(len->x < 0)
        len->x = 0;
    if(len->y > cube->screen_height)
        len->y = cube->screen_height;
    else if(len->y < 0)
        len->y = 0;
}

uint32_t shade_color(uint32_t base, double distance)
{
    // Extract RGBA
    uint8_t r = (base >> 24) & 0xFF;
    uint8_t g = (base >> 16) & 0xFF;
    uint8_t b = (base >> 8) & 0xFF;
    uint8_t a = base & 0xFF;

    // Fade factor: closer = brighter, farther = darker
    double factor = 1.0 / (1.0 + distance * 0.03); // tweak 0.01
    // if(factor < 0.2) factor = 0.2; // keep minimum brightness

    r = (uint8_t)(r * factor);
    g = (uint8_t)(g * factor);
    b = (uint8_t)(b * factor);

    return (r << 24 | g << 16 | b << 8 | a);
}

// void ft_mini_map(t_cube *cube){
//     int x;
//     int y;

//     x = 0;
//     while(x < MAP_X + MAP_SIZE){
//         y = 0;
//         while(y < MAP_Y + MAP_SIZE){
//             if(cube->map[(int)(y / GRID_SIZE)][(int)(x / GRID_SIZE)] == 1)
//                 cube->prev_buffer[(cube->screen_width * (int)y * 4) + ((int)x * 4) + 0] = 255;
//                 cube->prev_buffer[(cube->screen_width * (int)y * 4) + ((int)x * 4) + 1] = 0;
//                 cube->prev_buffer[(cube->screen_width * (int)y * 4) + ((int)x * 4) + 2] = 0;
//                 cube->prev_buffer[(cube->screen_width * (int)y * 4) + ((int)x * 4) + 3] = 255;
//             else
//             y++;
//         }
//         x++; 
//     }
// }

void ft_draw_texture(t_cube *cube, t_ray *ray, t_vect2 start, t_vect2 end, double len)
{
    t_vect2 ratio;
    t_vect2 cords;

    if(cube->texture == NULL)
    {
        printf("textuh aint loadin twin :)\n");
        exit(1);
    }
    cords.y = 0;
    ratio.y = cube->texture->height / len;
    if(check_screen_limits(cube, start) && start.y <= 0)
    {
        cords.y = ratio.y * ((-1) * start.y);
        start.y = 0;
    }
    cords.x = cube->texture->width * ray->normal_dst;
    if(cords.x < 0)
        cords.x = 0;
    if(cords.x >= cube->texture->width)
        cords.x = cube->texture->width - 1;
    double tmp = 1.0 - (ray->length / MAX_DST);
    if(tmp > 1.0)
        tmp = 1.0;
    else if(tmp < 0.0)
        tmp = 0.0;
    while(start.y < cube->screen_height && start.y < end.y && cords.y < cube->texture->height)
    {

        // if ((((int)start.x + (int)start.y) % 2) != cube->grain)
        // {
        //     // We skip drawing, BUT we must keep the texture aligned!
        //     cords.y += ratio.y;
        //     start.y++;
        //     continue; 
        // }

        // uint8_t r = cube->texture->pixels[k + 0] * (tmp);
        // uint8_t g = cube->texture->pixels[k + 1] * (tmp);
        // uint8_t b = cube->texture->pixels[k + 2] * (tmp);
        // uint8_t a = cube->texture->pixels[k + 3];

        // uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
        if(!check_screen_limits(cube, start)){
            int k = ((int)cords.x * cube->texture->bytes_per_pixel) + (cube->texture->width * cube->texture->bytes_per_pixel * (int)cords.y);
            cube->prev_buffer[(cube->screen_width * (int)start.y * 4) + ((int)start.x * 4) + 0] = cube->texture->pixels[k + 0] * (tmp);
            cube->prev_buffer[(cube->screen_width * (int)start.y * 4) + ((int)start.x * 4) + 1] = cube->texture->pixels[k + 1] * (tmp);
            cube->prev_buffer[(cube->screen_width * (int)start.y * 4) + ((int)start.x * 4) + 2] = cube->texture->pixels[k + 2] * (tmp);
            cube->prev_buffer[(cube->screen_width * (int)start.y * 4) + ((int)start.x * 4) + 3] = cube->texture->pixels[k + 3];
            // mlx_put_pixel(cube->image, start.x, start.y, color);
        }
        cords.y += ratio.y;
        start.y++;
    }
}

    void ft_draw_world(t_cube *cube)
    {
        t_vect2 start;
        t_vect2 end;
        double len;
        int j;
        int i;

        start.x = (cube->screen_width - (cube->line_girth * cube->res)) / 2;
        ft_rectangle(cube, (t_vect2){0, 0, 0, 0}, (t_vect2){start.x, cube->screen_height, 0, 0}, 0x000000ff);
        ft_rectangle(cube, (t_vect2){cube->screen_width - start.x, 0, 0, 0}, (t_vect2){cube->screen_width, cube->screen_height, 0, 0}, 0x000000ff);
        i = 0;
        while(i <= cube->res)
        {
            j = 0;
            double length = cube->rays[i].length * cos(cube->rays[i].real_angle - cube->player.angle);
            len = ((GRID_SIZE) / length) * cube->proj_dst;
            double proj_z_offset = (((GRID_SIZE / 2.0) - CAM_H) / length) * cube->proj_dst;
            start.y = ((cube->screen_height - len) / 2) + cube->pitch - proj_z_offset;
            end.x = start.x;
            end.y = start.y + len;
            while(j < cube->line_girth)
            {
                if((int)start.x < cube->screen_width)
                    cube->z_buffer[(int)start.x] = length;
                ft_draw_texture(cube, &cube->rays[i], start, end, len);
                start.x++;
                end.x++;
                j++;
            }
            i++;
        }
    }
    // double DirX = cos(cube->player.angle);
    // double DirY = sin(cube->player.angle);

bool is_looking(t_cube *cube, t_enemy *enemy){
    if(enemy->dead == true)
        return false;
    if((enemy->start_x < cube->screen_width / 2) && (enemy->end_x > cube->screen_width / 2) &&
     (enemy->start_y < cube->screen_height / 2) && (enemy->end_y > cube->screen_height / 2))
     return true;
    return false;
}


// bool is_looking(t_cube *cube, t_enemy *enemy){
//     double angle_to_enemy = atan2(enemy->y - cube->player.y, enemy->x - cube->player.x);

//     double angle_diff = angle_to_enemy - cube->player.angle;

//     while(angle_diff < -PI)
//         angle_diff += 2 * PI;
//     while(angle_diff > PI)
//         angle_diff -= 2 * PI;

//     angle_diff = fabs(angle_diff);
    
//     if(angle_diff > enemy->max_hit_angle)
//         return false;
//     return true;
// }

// bool is_looking(t_cube *cube, t_enemy *enemy){

//     int hitbox_len = 50;

//     float enemy_dir_x = cube->player.x - enemy->x;
//     float enemy_dir_y = cube->player.y - enemy->y;

//     float len = sqrt(enemy_dir_x * enemy_dir_x + enemy_dir_y * enemy_dir_y);

//     if (len == 0) len = 1;

//     t_vect2 enemy_dir = (t_vect2){enemy_dir_x / len, enemy_dir_y / len, 0, 0};

//     t_vect2 player_dir = (t_vect2){cos(cube->player.angle), sin(cube->player.angle), 0, 0};

//     t_vect2 enemy_hitbox = (t_vect2){-1 * enemy_dir.y * hitbox_len, enemy_dir.x * hitbox_len, 0, 0};

//     t_vect2 gap_vect = (t_vect2){(enemy->x - (enemy_hitbox.x / 2)) - cube->player.x, (enemy->y - (enemy_hitbox.y / 2)) - cube->player.y, 0, 0};

//     float denom = (player_dir.x * enemy_hitbox.y) - (player_dir.y * enemy_hitbox.x);

//     if(fabs(denom) < 0.001) return false;

//     float hit_dir = ((gap_vect.x * enemy_hitbox.y) - (gap_vect.y * enemy_hitbox.x)) / denom;

//     float hit_check = ((gap_vect.x * player_dir.y) - (gap_vect.y * player_dir.x)) / denom;

//     if(hit_dir > 0.0 && hit_check >= 0.0 && hit_check <= 1.0) return true;

//     return false;
// }

void ft_projectile(t_cube *cube, t_projectile *projectile){

    if(projectile->in_use == 0)
        return;

    double player_dst = sqrt((cube->player.x - projectile->x) * (cube->player.x - projectile->x) + (cube->player.y - projectile->y) * (cube->player.y - projectile->y));

    if(player_dst < HITBOX_DST){
        printf("player shot!\n");
        cube->player.HP -= projectile->DMG;
        cube->player.hit = true;
        projectile->in_use = 0;
        return;
    }

    if(cube->map[(int)((projectile->y + (projectile->dir.y * projectile->speed)) / GRID_SIZE)][(int)(projectile->x / GRID_SIZE)] == 1)
        return((void)(projectile->in_use = 0));
    if(cube->map[(int)(projectile->y / GRID_SIZE)][(int)((projectile->x + (projectile->dir.x * projectile->speed)) / GRID_SIZE)] == 1)
        return((void)(projectile->in_use = 0));


    projectile->y += projectile->dir.y * projectile->speed;
    projectile->x += projectile->dir.x * projectile->speed;

    double angle_diff = atan2(projectile->y - cube->player.y, projectile->x - cube->player.x);
    double tetha_delta = angle_diff - cube->player.angle;
    while(tetha_delta > PI)
        tetha_delta -= 2 * PI;
    while(tetha_delta < -PI)
        tetha_delta += 2 * PI;
    
    int midX = ((0.5 * cube->screen_width)) + (tan(tetha_delta) * cube->proj_dst);
    double dst = sqrt((projectile->x - cube->player.x) * (projectile->x - cube->player.x) + (projectile->y - cube->player.y) * (projectile->y - cube->player.y)) * cos(tetha_delta);

    if(dst < 0.1) 
    return;

    double tmp = 1.0 - (dst / MAX_DST);
    if(tmp > 1.0)
        tmp = 1.0;
    else if(tmp < 0.0)
        tmp = 0.0;

    double height = (GRID_SIZE / dst) * cube->proj_dst;

    double scale_ratio = projectile->texture->height / height;

    double proj_z_offset = (((GRID_SIZE / 2.0) - CAM_H) / dst) * cube->proj_dst;
    int start_x = midX - (projectile->texture->width / scale_ratio) / 2;
    int start_y = ((cube->screen_height / 2.0) + cube->pitch - proj_z_offset) - (projectile->texture->height / scale_ratio) / 2;
    int const_y = start_y;
    int end_x = start_x + (projectile->texture->width / scale_ratio);
    int end_y = start_y + (projectile->texture->height / scale_ratio);
    
    double tex_x = 0;
    double tex_y = 0;

    if (start_x < 0) {
        tex_x += (-start_x) * scale_ratio;
        start_x = 0;
    }

    if (start_x >= cube->screen_width) return;
    if (end_x > cube->screen_width) end_x = cube->screen_width;

    if (start_y < 0) {
        tex_y = (-start_y) * scale_ratio;
        start_y = 0;
    }
    if (start_y >= cube->screen_height) return;

    if (end_x > cube->screen_width) end_x = cube->screen_width;
    if (end_y > cube->screen_height) end_y = cube->screen_height;

    while(start_x < end_x){
        start_y = const_y;
        int x = (int)tex_x;
        if (x >= (int)projectile->texture->width) x = projectile->texture->width - 1;
        if (x < 0) x = 0;
        tex_y = 0;
        if(cube->z_buffer[start_x] > dst){
            cube->z_buffer[start_x] = dst;
            while(start_y < end_y){
                int y = (int)tex_y;
                if (y >= (int)projectile->texture->height) y = projectile->texture->height - 1;
                if (y < 0) y = 0;
    
                if(!check_screen_limits(cube, (t_vect2){start_x, start_y, 0, 0})){
                    int k = (x * projectile->texture->bytes_per_pixel) + (projectile->texture->width * projectile->texture->bytes_per_pixel * y);
                    if(projectile->texture->pixels[k + 3] > 128){
                        cube->prev_buffer[(cube->screen_width * (int)start_y * 4) + ((int)start_x * 4) + 0] = projectile->texture->pixels[k + 0] * tmp;
                        cube->prev_buffer[(cube->screen_width * (int)start_y * 4) + ((int)start_x * 4) + 1] = projectile->texture->pixels[k + 1] * tmp;
                        cube->prev_buffer[(cube->screen_width * (int)start_y * 4) + ((int)start_x * 4) + 2] = projectile->texture->pixels[k + 2] * tmp;
                        cube->prev_buffer[(cube->screen_width * (int)start_y * 4) + ((int)start_x * 4) + 3] = projectile->texture->pixels[k + 3];
                    }
                }
                start_y++;
                tex_y += scale_ratio;
            }
        }

        tex_x += scale_ratio;
        start_x++;
    }
}

void ft_init_projectile(t_cube *cube, t_enemy *enemy, t_vect2 *dir){
    t_projectile proj;

    proj.x = enemy->x;
    proj.y = enemy->y;
    // proj.dir = (t_vect2){-1 * dir->x, -1 * dir->y, 0, 0};
    proj.dir = *dir;
    proj.in_use = 1;
    proj.DMG = enemy->DMG;
    proj.texture = cube->texture6;
    proj.dst_traveled = 0;
    proj.speed = 7;

    int i = 0;
    while(i < MAX_PROJECTILES){
        if(cube->projectiles[i].in_use == 0){
            cube->projectiles[i] = proj;
            break;
        }
        i++;
    }
}

void ft_enemy(t_cube *cube, t_enemy *enemy, mlx_texture_t *texture){

    struct timeval tv;
    gettimeofday(&tv, NULL);
    long current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

    if(enemy->dead){
        if(enemy->blood_frame_index >= 12)
            return;
        if(current_time - enemy->blood_time > BLOOD_ANIM_DELAY){
            enemy->blood_time = current_time;
            enemy->blood_frame_index++;
        }
        if(enemy->blood_frame_index < 12)
            texture = cube->blood_explosion.frame[enemy->blood_frame_index];
        else
            return;
    }
    
    if(enemy->dead == false && enemy->HP <= 0) 
    {
        texture = cube->blood_explosion.frame[enemy->blood_frame_index];
        enemy->blood_time = current_time;
        enemy->dead = true;
    }

    enemy->player_dst = sqrt((cube->player.x - enemy->x) * (cube->player.x - enemy->x) + (cube->player.y - enemy->y) * (cube->player.y - enemy->y));
    if(enemy->player_dst > MAX_DST)
        return;
    t_vect2 player_dir = (t_vect2){(cube->player.x - enemy->x) / enemy->player_dst, (cube->player.y - enemy->y) / enemy->player_dst, 0, 0};
    player_dir.x *= ENEMY_SPEED;
    player_dir.y *= ENEMY_SPEED;

    if(enemy->dead == false && enemy->player_dst < MIN_ATK_DST){
        if(enemy->delay == false){
            printf("enemy has shot!\n");
            ft_init_projectile(cube, enemy, &player_dir);
            if(cube->player.HP < 0) cube->player.HP = 0;
            enemy->atk_time = tv.tv_sec;
            enemy->delay = true;
        }
    }

    // if(cube->player.delay == true){
    //     if((int)(tv.tv_sec - cube->player.atk_time) == cube->player.atk_delay)
    //         cube->player.delay = false;
    // }


    if(enemy->delay == true){
        if((int)(tv.tv_sec - enemy->atk_time) == enemy->atk_delay)
            enemy->delay = false;
    }

    // if(is_looking(cube, enemy) == true)
    //     printf("LOOKING AT ENEMY HITBOX!!\n");

    // printf("enemy->player_dst : %lf, enemy : (%lf, %lf), player_dir : (%lf, %lf)\n", enemy->player_dst, enemy->x, enemy->y, player_dir.x, player_dir.y);
    // if(enemy->player_dst < ENEMY_RADIUS && enemy->player_dst > 10.0){
    //     if(cube->map[(int)((enemy->y + player_dir.y) / GRID_SIZE)][(int)(enemy->x / GRID_SIZE)] != 1)
    //         enemy->y += player_dir.y;
    //     if(cube->map[(int)(enemy->y / GRID_SIZE)][(int)((enemy->x + player_dir.x) / GRID_SIZE)] != 1)
    //         enemy->x += player_dir.x;
    // }

    double angle_diff = atan2(enemy->y - cube->player.y, enemy->x - cube->player.x);
    double tetha_delta = angle_diff - cube->player.angle;
    while(tetha_delta > PI)
        tetha_delta -= 2 * PI;
    while(tetha_delta < -PI)
        tetha_delta += 2 * PI;
    
    int midX = ((0.5 * cube->screen_width)) + (tan(tetha_delta) * cube->proj_dst);
    double dst = sqrt((enemy->x - cube->player.x) * (enemy->x - cube->player.x) + (enemy->y - cube->player.y) * (enemy->y - cube->player.y)) * cos(tetha_delta);

    if(dst < 0.1) 
    return;

    double tmp = 1.0 - (dst / MAX_DST);
    if(tmp > 1.0)
        tmp = 1.0;
    else if(tmp < 0.0)
        tmp = 0.0;

    double height = (GRID_SIZE / dst) * cube->proj_dst;

    double scale_ratio = texture->height / height;

    double proj_z_offset = (((GRID_SIZE / 2.0) - CAM_H) / dst) * cube->proj_dst;
    int start_x = midX - (texture->width / scale_ratio) / 2;
    int start_y = ((cube->screen_height / 2.0) + cube->pitch - proj_z_offset) - (texture->height / scale_ratio) / 2;
    int const_y = start_y;
    int end_x = start_x + (texture->width / scale_ratio);
    int end_y = start_y + (texture->height / scale_ratio);

    enemy->start_y = start_y;
    enemy->end_y = end_y;
    enemy->start_x = start_x;
    enemy->end_x = end_x;

    // if(is_looking(cube, enemy) && (((start_y + 12) < cube->screen_height / 2) && ((end_y - 12) > cube->screen_height / 2)) && (enemy->player_dst < cube->rays[cube->res / 2].length)){
    //     if(mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT) && (cube->player.delay == false)){
    //         printf("enemy attacked! enemy HP: %d\n", enemy->HP);
    //         enemy->HP -= cube->player.DMG;
    //         if(cube->player.delay == false){
    //             cube->player.atk_time = tv.tv_sec;
    //             cube->player.delay = true;
    //         }
    //     }
    // }


    double tex_x = 0;
    double tex_y = 0;

    if (start_x < 0) {
        tex_x += (-start_x) * scale_ratio;
        start_x = 0;
    }

    if (start_x >= cube->screen_width) return;
    if (end_x > cube->screen_width) end_x = cube->screen_width;

    if (start_y < 0) {
        tex_y = (-start_y) * scale_ratio;
        start_y = 0;
    }
    if (start_y >= cube->screen_height) return;

    if (end_x > cube->screen_width) end_x = cube->screen_width;
    if (end_y > cube->screen_height) end_y = cube->screen_height;

    while(start_x < end_x){
        start_y = const_y;
        int x = (int)tex_x;
        if (x >= (int)texture->width) x = texture->width - 1;
        if (x < 0) x = 0;
        tex_y = 0;
        if(cube->z_buffer[start_x] > dst){
            cube->z_buffer[start_x] = dst;
            while(start_y < end_y){
                int y = (int)tex_y;
                if (y >= (int)texture->height) y = texture->height - 1;
                if (y < 0) y = 0;
    
                if(!check_screen_limits(cube, (t_vect2){start_x, start_y, 0, 0})){
                    int k = (x * texture->bytes_per_pixel) + (texture->width * texture->bytes_per_pixel * y);
                    if(texture->pixels[k + 3] > 128){
                        cube->prev_buffer[(cube->screen_width * (int)start_y * 4) + ((int)start_x * 4) + 0] = texture->pixels[k + 0] * tmp;
                        cube->prev_buffer[(cube->screen_width * (int)start_y * 4) + ((int)start_x * 4) + 1] = texture->pixels[k + 1] * tmp;
                        cube->prev_buffer[(cube->screen_width * (int)start_y * 4) + ((int)start_x * 4) + 2] = texture->pixels[k + 2] * tmp;
                        cube->prev_buffer[(cube->screen_width * (int)start_y * 4) + ((int)start_x * 4) + 3] = texture->pixels[k + 3];
                    }
                }
                start_y++;
                tex_y += scale_ratio;
            }
        }

        tex_x += scale_ratio;
        start_x++;
    }
}

// void ft_draw_sprite_stripe(t_cube *cube, t_vect2 start, double len, int tex_x)
// {
//     t_vect2 ratio;
//     t_vect2 cords;
//     int     tex_y;
//     int     pixel_index;
//     int     tex_index;

//     // 1. Setup Scaling (Same as your wall logic)
//     ratio.y = (double)cube->texture4->height / len;
//     cords.y = 0;
    
//     // 2. Vertical Clipping (Top) - Handle when sprite is taller than screen
//     if (start.y < 0)
//     {
//         cords.y = ratio.y * ((-1) * start.y);
//         start.y = 0;
//     }

//     // 3. Draw Loop
//     // Stop at bottom of screen OR end of sprite
//     double end_y = start.y + len; 
//     if (end_y > cube->screen_height) 
//         end_y = cube->screen_height;

//     while (start.y < end_y && cords.y < cube->texture4->height)
//     {
//         tex_y = (int)cords.y;
        
//         // Calculate index in texture array
//         tex_index = (tex_x * cube->texture4->bytes_per_pixel) + 
//                     (cube->texture4->width * cube->texture4->bytes_per_pixel * tex_y);

//         // Get Alpha (Transparency)
//         uint8_t color_a = cube->texture4->pixels[tex_index + 3];

//         // Only draw if pixel is NOT transparent
//         if (color_a != 0) 
//         {
//             pixel_index = (cube->screen_width * (int)start.y * 4) + ((int)start.x * 4);

//             if (pixel_index >= 0 && pixel_index < cube->screen_width * cube->screen_height * 4)
//             {
//                 cube->prev_buffer[pixel_index + 0] = cube->texture4->pixels[tex_index + 0];
//                 cube->prev_buffer[pixel_index + 1] = cube->texture4->pixels[tex_index + 1];
//                 cube->prev_buffer[pixel_index + 2] = cube->texture4->pixels[tex_index + 2];
//                 cube->prev_buffer[pixel_index + 3] = 255;
//             }
//         }
        
//         cords.y += ratio.y;
//         start.y++;
//     }
// }

// void ft_render_enemy(t_cube *cube)
// {
//     // --- 1. CALC ANGLES ---
//     double sprite_dir = atan2(cube->enemy->y - cube->player.y, cube->enemy.x - cube->player.x);
//     double theta_delta = sprite_dir - cube->player.angle;

//     // Fix 360 wrap-around (Normalize angle between -PI and +PI)
//     if (theta_delta > PI) 
//         theta_delta -= 2 * PI;
//     if (theta_delta < -PI) 
//         theta_delta += 2 * PI;

//     // --- 2. CALC DISTANCE & HEIGHT ---
//     double dist = sqrt(pow(cube->enemy.x - cube->player.x, 2) + pow(cube->enemy.y - cube->player.y, 2));
    
//     // Fix Fisheye
//     double fixed_dist = dist * cos(theta_delta);

//     // Safety: Don't divide by zero or draw if behind player
//     if (fixed_dist < 0.1) 
//         return; 

//     // Calculate Height (Same formula as walls)
//     double sprite_height = (GRID_SIZE / fixed_dist) * PROJ_DST;
//     double sprite_width  = sprite_height; // Assume square sprite

//     // --- 3. CALC SCREEN POSITIONS ---
//     // Find where the MIDDLE of the sprite is on screen
//     int screen_mid_x = (cube->screen_width / 2) + (tan(theta_delta) * PROJ_DST);
    
//     int start_x = screen_mid_x - (sprite_width / 2);
//     int end_x   = screen_mid_x + (sprite_width / 2);
//     int start_y = (cube->screen_height - sprite_height) / 2;

//     // --- 4. DRAW COLUMNS ---
//     t_vect2 pos;
//     pos.y = start_y;
    
//     int x = start_x;
//     while (x < end_x)
//     {
//         // Only draw if column is within screen bounds
//         if (x >= 0 && x < cube->screen_width)
//         {
//             pos.x = x;
            
//             // Calculate which column of the texture to use
//             // logic: (current_x_offset / total_width) * texture_width
//             int tex_x = (int)((x - start_x) * (double)cube->texture4->width / sprite_width);
            
//             // Safety clamp for texture index
//             if (tex_x < 0) tex_x = 0;
//             if (tex_x >= (int)cube->texture4->width) tex_x = (int)cube->texture4->width - 1;

//             ft_draw_sprite_stripe(cube, pos, sprite_height, tex_x);
//         }
//         x++;
//     }
// }



// void ft_floor(t_cube *cube)
// {
//     double dirX = cos(cube->player.angle);
//     double dirY = sin(cube->player.angle);

//     // Camera plane (perpendicular to dir)
//     double planeX = -dirY * (FOV / 10);
//     double planeY =  dirX * (FOV / 10);

//     double playerX = cube->player.x / GRID_SIZE;
//     double playerY = cube->player.y / GRID_SIZE;

//     double posZ = 0.5 * cube->screen_height; // cameraHeight = 0.5

//     for (int i = cube->screen_height / 2; i < cube->screen_height; i++)
//     {
//         double p = i - cube->screen_height / 2.0;
//         double rowDist = posZ / p;

//         // World positions at left & right
//         double floorXLeft  = playerX + rowDist * (dirX - planeX);
//         double floorYLeft  = playerY + rowDist * (dirY - planeY);
//         double floorXRight = playerX + rowDist * (dirX + planeX);
//         double floorYRight = playerY + rowDist * (dirY + planeY);

//         double stepX = (floorXRight - floorXLeft) / cube->screen_width;
//         double stepY = (floorYRight - floorYLeft) / cube->screen_width;

//         double floorX = floorXLeft;
//         double floorY = floorYLeft;

//         for (int j = 0; j < cube->screen_width; j++)
//         {
//             // fractional parts → texture coords
//             double fracX = fmod(floorX, 1.0);
//             double fracY = fmod(floorY, 1.0);
//             if (fracX < 0) fracX += 1.0;
//             if (fracY < 0) fracY += 1.0;

//             int texX = (int)(fracX * cube->texture->width);
//             int texY = (int)(fracY * cube->texture->height);

//             int idx = (texY * cube->texture->width + texX) * cube->texture->bytes_per_pixel;

//             uint8_t r = cube->texture->pixels[idx + 0];
//             uint8_t g = cube->texture->pixels[idx + 1];
//             uint8_t b = cube->texture->pixels[idx + 2];
//             uint8_t a = cube->texture->pixels[idx + 3];

//             uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;

//             mlx_put_pixel(cube->image, j, i, color);

//             floorX += stepX;
//             floorY += stepY;
//         }
//     }
// }
#include <string.h>
// void ft_shader(t_cube *cube)
// {
//     int x;
//     int y;

//     x = 0;
//     while(x < cube->screen_width)
//     {
//         y = 0;
//         while(y < cube->screen_height)
//         {
            
//             y++;
//         }
//         x++;
//     }
// }

// void ft_floor(t_cube *cube)
// {
    
//     double DirX = cos(cube->player.angle);
//     double DirY = sin(cube->player.angle);
//     double PlaneX = -DirY * (HALF_FOV_RAD);
//     double PlaneY = DirX * (HALF_FOV_RAD);
//     t_vect2 RayDirL = (t_vect2){DirX - PlaneX, DirY - PlaneY,0 ,0};
//     t_vect2 RayDirR = (t_vect2){DirX + PlaneX, DirY + PlaneY,0 ,0};
//     t_vect2 PlayerPos = (t_vect2){(cube->player.x), (cube->player.y), 0, 0};
//     // t_vect2 PlayerPos = (t_vect2){cube->player.x, cube->player.y, 0, 0};
//     // double posZ = cube->screen_height / 2.0;
//     // double posZ = (CAM_H) * PROJ_DST;
//     double posZ = V_PROJ_DST;
//     int i = posZ + 1;
//     while(i < cube->screen_height)
//     {
//         double p = (float)i - cube->screen_height / 2.0;   // distance from horizon in screen pixels
//         double rowDst = posZ / p;
//         t_vect2 floorL = (t_vect2){(PlayerPos.x) + rowDst * RayDirL.x, (PlayerPos.y) + rowDst * RayDirL.y, 0, 0};
//         t_vect2 floorR = (t_vect2){(PlayerPos.x) + rowDst * RayDirR.x, (PlayerPos.y) + rowDst * RayDirR.y, 0, 0};

//         t_vect2 step = (t_vect2){(floorR.x - floorL.x) / cube->screen_width, (floorR.y - floorL.y) / cube->screen_width, 0, 0};

//         t_vect2 ft_floor = (t_vect2){floorL.x, floorL.y, 0, 0};

//         int j = 0;
//         while(j < cube->screen_width)
//         {
//             double fracX = fmod(ft_floor.x, 1.0);
//             double fracY = fmod(ft_floor.y, 1.0);
//             if (fracX < 0) fracX += 1.0;
//             if (fracY < 0) fracY += 1.0;

//             // printf("ft_floorX : %lf, ft_floorY : %lf, gridX : %lf, gridY : %lf\n", ft_floor.x, ft_floor.y, fracX, fracY);

//             int texX = (int)(fracX * cube->texture2->width);
//             int texY = (int)(fracY * cube->texture2->height);
//             int k = ((cube->texture2->bytes_per_pixel * texY * cube->texture2->width) + (texX * cube->texture2->bytes_per_pixel));
//             uint8_t r = cube->texture2->pixels[k + 0];
//             uint8_t g = cube->texture2->pixels[k + 1];
//             uint8_t b = cube->texture2->pixels[k + 2];
//             uint8_t a = cube->texture2->pixels[k + 3];
//             uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
//             t_vect2 coords = (t_vect2){j, i, 0, 0};
//             if(!check_screen_limits(coords))
//                 mlx_put_pixel(cube->image, j, i, color);
//             ft_floor.x += step.x;
//             ft_floor.y += step.y;
//             j++;
//         }
//         i++;
//     }
// }
void ft_ceiling(t_cube *cube)
{
    double DirX = cos(cube->player.angle);
    double DirY = sin(cube->player.angle);
    double PlaneX = -DirY * (HALF_FOV_RAD);
    double PlaneY = DirX * (HALF_FOV_RAD);
    t_vect2 RayDirL = (t_vect2){DirX - PlaneX, DirY - PlaneY,0 ,0};
    t_vect2 RayDirR = (t_vect2){DirX + PlaneX, DirY + PlaneY,0 ,0};

    int i = 0;
    while(i < cube->screen_height / 2)
    {
        // if replace cube->screen_height with cube->screen_width you get ceiling textures PS: found it by accident :P
        double p = (cube->screen_height / 2.0) - (float)i;   // distance from horizon in screen pixels
        double rowDst = (CAM_H * PROJ_DST) / p;

        t_vect2 floorL = (t_vect2){(cube->player.x) + rowDst * RayDirL.x, (cube->player.y) + rowDst * RayDirL.y, 0, 0};
        t_vect2 floorR = (t_vect2){(cube->player.x) + rowDst * RayDirR.x, (cube->player.y) + rowDst * RayDirR.y, 0, 0};

        t_vect2 step = (t_vect2){(floorR.x - floorL.x) / cube->screen_width, (floorR.y - floorL.y) / cube->screen_width, 0, 0};
        t_vect2 ft_floor = (t_vect2){floorL.x, floorL.y, 0, 0};

        double tmp = 1.0 - (rowDst / MAX_DST);
        if(tmp > 1.0)
            tmp = 1.0;
        else if(tmp < 0.0)
            tmp = 0.0;

        int j = 0;
        while(j < cube->screen_width)
        {
            double fracX = fmod(ft_floor.x / GRID_SIZE, 1.0);
            double fracY = fmod(ft_floor.y / GRID_SIZE, 1.0);
            
            if (fracX < 0) fracX += 1.0;
            if (fracY < 0) fracY += 1.0;

            int texX = (int)(fracX * cube->texture3->width);
            int texY = (int)(fracY * cube->texture3->height);
            
            int k = ((cube->texture3->bytes_per_pixel * texY * cube->texture3->width) + (texX * cube->texture3->bytes_per_pixel));
            uint8_t r = cube->texture3->pixels[k + 0] * tmp;
            uint8_t g = cube->texture3->pixels[k + 1] * tmp;
            uint8_t b = cube->texture3->pixels[k + 2] * tmp;
            uint8_t a = cube->texture3->pixels[k + 3];
            uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
            t_vect2 coords = (t_vect2){j, i, 0, 0};
            int iter = 0;
            while(iter < cube->line_girth){
                if(!check_screen_limits(cube, coords))
                    mlx_put_pixel(cube->image, j, i, color);
                ft_floor.x += step.x;
                ft_floor.y += step.y;
                j++;
                iter++;
            }
        }
        i++;
    }
}
void ft_floor(t_cube *cube)
{
    double DirX = cos(cube->player.angle);
    double DirY = sin(cube->player.angle);
    double PlaneX = -DirY * (HALF_FOV_RAD);
    double PlaneY = DirX * (HALF_FOV_RAD);
    t_vect2 RayDirL = (t_vect2){DirX - PlaneX, DirY - PlaneY,0 ,0};
    t_vect2 RayDirR = (t_vect2){DirX + PlaneX, DirY + PlaneY,0 ,0};

    int i = (cube->screen_height / 2);
    while(i < cube->screen_height)
    {
        // if replace cube->screen_height with cube->screen_width you get ceiling textures PS: found it by accident :P
        double p = (float)i - cube->screen_height / 2.0;
        double rowDst = (CAM_H * PROJ_DST) / p;

        t_vect2 floorL = (t_vect2){(cube->player.x) + rowDst * RayDirL.x, (cube->player.y) + rowDst * RayDirL.y, 0, 0};
        t_vect2 floorR = (t_vect2){(cube->player.x) + rowDst * RayDirR.x, (cube->player.y) + rowDst * RayDirR.y, 0, 0};

        t_vect2 step = (t_vect2){(floorR.x - floorL.x) / cube->screen_width, (floorR.y - floorL.y) / cube->screen_width, 0, 0};
        t_vect2 ft_floor = (t_vect2){floorL.x, floorL.y, 0, 0};

        double tmp = 1.0 - (rowDst / MAX_DST);
        if(tmp > 1.0)
            tmp = 1.0;
        else if(tmp < 0.0)
            tmp = 0.0;

        int j = 0;
        while(j < cube->screen_width)
        {
            double fracX = fmod(ft_floor.x / GRID_SIZE, 1.0);
            double fracY = fmod(ft_floor.y / GRID_SIZE, 1.0);
            
            if (fracX < 0) fracX += 1.0;
            if (fracY < 0) fracY += 1.0;

            int texX = (int)(fracX * cube->texture2->width);
            int texY = (int)(fracY * cube->texture2->height);
            
            int k = ((cube->texture2->bytes_per_pixel * texY * cube->texture2->width) + (texX * cube->texture2->bytes_per_pixel));
            uint8_t r = cube->texture2->pixels[k + 0] * tmp;
            uint8_t g = cube->texture2->pixels[k + 1] * tmp;
            uint8_t b = cube->texture2->pixels[k + 2] * tmp;
            uint8_t a = cube->texture2->pixels[k + 3];
            uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
            t_vect2 coords = (t_vect2){j, i, 0, 0};
            int iter = 0;
            while(iter < cube->line_girth){
                if(!check_screen_limits(cube, coords))
                    mlx_put_pixel(cube->image, j, i, color);
                ft_floor.x += step.x;
                ft_floor.y += step.y;
                j++;
                iter++;
            }
        }
        i++;
    }
}

void ft_crt_vhs_effect(t_cube *cube)
{
    int x, y;
    int tmp, src_tmp;
    uint8_t *tmp_pixels;
    int width = cube->image->width;
    int height = cube->image->height;
    int bpp = 4;

    srand(time(NULL));
    tmp_pixels = malloc(width * height * bpp);
    if (!tmp_pixels)
        return;
    memcpy(tmp_pixels, cube->image->pixels, width * height * bpp);
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            tmp = (y * width + x) * bpp;
            float scanline = (y % 2 == 0) ? 0.5f : 1.0f;
            int r_x = x - 7;
            int g_x = x;
            int b_x = x + 7;
            if (r_x < 0) r_x = 0;
            if (b_x >= width) b_x = width - 1;
            src_tmp = (y * width + r_x) * bpp;
            uint8_t r = tmp_pixels[src_tmp + 0];
            src_tmp = (y * width + g_x) * bpp;
            uint8_t g = tmp_pixels[src_tmp + 1];
            src_tmp = (y * width + b_x) * bpp;
            uint8_t b = tmp_pixels[src_tmp + 2];
            uint8_t a = tmp_pixels[(y * width + x) * bpp + 3];
            int noise = (rand() % 20);
            r = (uint8_t)fmax(0, fmin(255, r * scanline + noise));
            g = (uint8_t)fmax(0, fmin(255, g * scanline + noise));
            b = (uint8_t)fmax(0, fmin(255, b * scanline + noise));
            cube->image->pixels[tmp + 0] = r;
            cube->image->pixels[tmp + 1] = g;
            cube->image->pixels[tmp + 2] = b;
            cube->image->pixels[tmp + 3] = a;
        }
    }
    free(tmp_pixels);
}

void ft_floor_ceiling(t_cube *cube){
    double DirX = cos(cube->player.angle);
    double DirY = sin(cube->player.angle);
    double PlaneX = -DirY * (cube->half_fov_rad);
    double PlaneY = DirX * (cube->half_fov_rad);
    t_vect2 RayDirL = (t_vect2){DirX - PlaneX, DirY - PlaneY,0 ,0};
    t_vect2 RayDirR = (t_vect2){DirX + PlaneX, DirY + PlaneY,0 ,0};
    double mid_point = (cube->screen_height / 2.0) + cube->pitch;

    double cam_height = CAM_H;
    double p = 0;
    mlx_texture_t *tex;
    int i = 0;
    while(i < cube->screen_height){
        if(i < mid_point){
            p = (mid_point) - (float)i;
            tex = cube->texture3;
            cam_height = GRID_SIZE - CAM_H;
        }
        else{
            p = (float)i - (mid_point);
            tex = cube->texture2;
            cam_height = CAM_H;
        }

        if(p == 0.0) p = 1.0;

        double rowDst = (cam_height * cube->proj_dst) / p;

        t_vect2 floorL = (t_vect2){(cube->player.x) + rowDst * RayDirL.x, (cube->player.y) + rowDst * RayDirL.y, 0, 0};
        t_vect2 floorR = (t_vect2){(cube->player.x) + rowDst * RayDirR.x, (cube->player.y) + rowDst * RayDirR.y, 0, 0};

        t_vect2 step = (t_vect2){(floorR.x - floorL.x) / cube->screen_width, (floorR.y - floorL.y) / cube->screen_width, 0, 0};
        t_vect2 ft_floor = (t_vect2){floorL.x, floorL.y, 0, 0};

        double tmp = 1.0 - (rowDst / MAX_DST);
        if(tmp > 1.0)
            tmp = 1.0;
        else if(tmp < 0.0)
            tmp = 0.0;

        int j = 0;
        while(j < cube->screen_width)
        {
            // if ((j + i) % 2 != cube->grain) 
            // {
            //     // Skip this pixel. The "Old" pixel remains on screen.
            //     ft_floor.x += step.x;
            //     ft_floor.y += step.y;
            //     j++;
            //     continue;
            // }
            double fracX = fmod(ft_floor.x / GRID_SIZE, 1.0);
            double fracY = fmod(ft_floor.y / GRID_SIZE, 1.0);
            
            if (fracX < 0) fracX += 1.0;
            if (fracY < 0) fracY += 1.0;

            int texX = (int)(fracX * tex->width);
            int texY = (int)(fracY * tex->height);
            
            int k = ((tex->bytes_per_pixel * texY * tex->width) + (texX * tex->bytes_per_pixel));
            uint8_t r = tex->pixels[k + 0] * (tmp);
            uint8_t g = tex->pixels[k + 1] * (tmp);
            uint8_t b = tex->pixels[k + 2] * (tmp);
            uint8_t a = tex->pixels[k + 3];

            // uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
            int y_iter = cube->screen_width * i * 4;
            t_vect2 coords = (t_vect2){j, i, 0, 0};
            int iter = 0;
            while(iter < cube->line_girth){
                if(!check_screen_limits(cube, coords)){
                    cube->prev_buffer[(y_iter) + (j * 4) + 0] = r;
                    cube->prev_buffer[(y_iter) + (j * 4) + 1] = g;
                    cube->prev_buffer[(y_iter) + (j * 4) + 2] = b;
                    cube->prev_buffer[(y_iter) + (j * 4) + 3] = a;
                }
                    // mlx_put_pixel(cube->image, j, i, color);
                ft_floor.x += step.x;
                ft_floor.y += step.y;
                j++;
                iter++;
            }
        }
        i++;
    }
}

void ft_upscaling(t_cube *cube, mlx_image_t *image){
    uint32_t *new = (uint32_t *)image->pixels;
    uint32_t *prev = (uint32_t *)cube->prev_buffer;
    int screen_H = cube->screen_height;
    int screen_W = cube->screen_width;        

    if(cube->state == GAME){
        prev = (uint32_t *)cube->new_buffer;
        screen_H = cube->screen_height - (cube->tilt_addition_height * 2);
        screen_W = cube->screen_width - (cube->tilt_addition_width * 2);
    }
    double iter_x = (double)screen_W / (double)cube->screen_width_buff;
    double iter_y = (double)screen_H / (double)cube->screen_height_buff;

    double prev_x = 0.0;
    double prev_y = 0.0;
    int new_x = 0;
    int new_y = 0;

    while(new_y < cube->screen_height_buff && prev_y < screen_H){
        new_x = 0;
        prev_x = 0.0;
        while(new_x < cube->screen_width_buff && prev_x < screen_W){
            new[(new_y * cube->screen_width_buff) + new_x] = prev[((int)prev_y * screen_W) + (int)prev_x];
            new_x++;
            prev_x += iter_x;
        }
        new_y++;
        prev_y += iter_y;
    }
}

void draw_crosshair(t_cube *cube){

    ft_rectangle(cube, cube->crosshair_hori_start, cube->crosshair_hori_end, cube->menu.settings.crosshair.color);
    ft_rectangle(cube, cube->crosshair_vert_start, cube->crosshair_vert_end, cube->menu.settings.crosshair.color);
}

void ft_prev_renderer(t_cube *cube, mlx_texture_t *texture, int start_x, int start_y){
    // int start_x = 0;
    // int start_y = 0;
    int x = 0;
    int y = 0;
    int tex_x;
    int tex_y;

    while(y < cube->screen_height){
        x = 0;
        tex_y = (double)(y) * ((double)(texture->height) / (double)(cube->screen_height));
        while(x < cube->screen_width){
            tex_x = (double)(x) * ((double)(texture->width) / (double)(cube->screen_width));
            int pixel_cords = ((y + start_y) * 4 * cube->screen_width) + ((x + start_x) * 4);
            int title_cords = (tex_y * 4 * texture->width) + (tex_x * 4);
            if(tex_x >= texture->width || tex_y >= texture->height || texture->pixels[tex_y * 4 * texture->width + tex_x * 4 + 3] < 50){
                // cube->prever[(y * 4 * cube->screen_width) + (x * 4) + 0] = 0;
                // cube->prever[(y * 4 * cube->screen_width) + (x * 4) + 1] = 0;
                // cube->prever[(y * 4 * cube->screen_width) + (x * 4) + 2] = 0;
                // cube->prever[(y * 4 * cube->screen_width) + (x * 4) + 3] = 255;
                x++;
                continue;
            }
            cube->prev_buffer[pixel_cords + 0] = texture->pixels[title_cords + 0];
            cube->prev_buffer[pixel_cords + 1] = texture->pixels[title_cords + 1];
            cube->prev_buffer[pixel_cords + 2] = texture->pixels[title_cords + 2];
            cube->prev_buffer[pixel_cords + 3] = texture->pixels[title_cords + 3];
            x++;
        }
        y++;
    }    
}

void ft_renderer(t_cube *cube, mlx_texture_t *texture, int start_x, int start_y){
    // int start_x = 0;
    // int start_y = 0;
    int x = 0;
    int y = 0;
    int tex_x;
    int tex_y;

    while(y < cube->screen_height_buff){
        x = 0;
        tex_y = (double)(y) * ((double)(texture->height) / (double)(cube->screen_height_buff));
        while(x < cube->screen_width_buff){
            tex_x = (double)(x) * ((double)(texture->width) / (double)(cube->screen_width_buff));
            int pixel_cords = ((y + start_y) * 4 * cube->screen_width_buff) + ((x + start_x) * 4);
            int title_cords = (tex_y * 4 * texture->width) + (tex_x * 4);
            if(tex_x >= texture->width || tex_y >= texture->height || texture->pixels[tex_y * 4 * texture->width + tex_x * 4 + 3] < 127){
                // cube->prev_buffer[(y * 4 * cube->screen_width_buff) + (x * 4) + 0] = 0;
                // cube->prev_buffer[(y * 4 * cube->screen_width_buff) + (x * 4) + 1] = 0;
                // cube->prev_buffer[(y * 4 * cube->screen_width_buff) + (x * 4) + 2] = 0;
                // cube->prev_buffer[(y * 4 * cube->screen_width_buff) + (x * 4) + 3] = 255;
                x++;
                continue;
            }
            cube->image->pixels[pixel_cords + 0] = texture->pixels[title_cords + 0];
            cube->image->pixels[pixel_cords + 1] = texture->pixels[title_cords + 1];
            cube->image->pixels[pixel_cords + 2] = texture->pixels[title_cords + 2];
            cube->image->pixels[pixel_cords + 3] = texture->pixels[title_cords + 3];
            x++;
        }
        y++;
    }    
}

void ft_fov_slider(t_cube *cube){
    int mouse_x;
    int mouse_y;
    int start_x = (double)(cube->menu.settings.fov.slider_end_x - cube->menu.settings.fov.slider_start_x) * ((double)(cube->init_fov - cube->menu.settings.fov.min_fov) / (double)(cube->menu.settings.fov.max_fov - cube->menu.settings.fov.min_fov));

    mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
    if(cube->menu.settings.mouse_held == FOV_SLIDER){
        start_x = mouse_x - cube->menu.settings.fov.slider_start_x;
        if (start_x > cube->menu.settings.fov.slider_end_x - cube->menu.settings.fov.slider_start_x)
            start_x = cube->menu.settings.fov.slider_end_x - cube->menu.settings.fov.slider_start_x;
        else if(start_x < 0)
            start_x = 0;
        cube->init_fov = ((cube->menu.settings.fov.max_fov - cube->menu.settings.fov.min_fov) * ((double)start_x / (double)(cube->menu.settings.fov.slider_end_x - cube->menu.settings.fov.slider_start_x))) + cube->menu.settings.fov.min_fov;
        cube->fov = cube->init_fov;
        cube->prev_fov = cube->init_fov;
        cube->proj_dst = (cube->screen_width / 2.0) / tan((cube->fov / 2.0) * RADIANT_RATE); // performance increase possible here
        cube->half_fov_rad = tan((cube->fov / 2.0) * RADIANT_RATE);
        cube->mod_rate = (cube->fov * RADIANT_RATE) / cube->res;
    }
    ft_renderer(cube, cube->menu.settings.fov.slider_1, start_x, 0);
}

void ft_mouse_sens(t_cube *cube){
    int mouse_x;
    int mouse_y;
    double start_x = (double)(cube->menu.settings.mouse_sens.slider_end_x - cube->menu.settings.mouse_sens.slider_start_x) * (((cube->mouse_sens) - cube->menu.settings.mouse_sens.min_sens) / (cube->menu.settings.mouse_sens.max_sens - cube->menu.settings.mouse_sens.min_sens));

    mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
    if(cube->menu.settings.mouse_held == MOUSE_SENS_SLIDER){
        start_x = mouse_x - cube->menu.settings.mouse_sens.slider_start_x;
        if (start_x > cube->menu.settings.mouse_sens.slider_end_x - cube->menu.settings.mouse_sens.slider_start_x)
            start_x = cube->menu.settings.mouse_sens.slider_end_x - cube->menu.settings.mouse_sens.slider_start_x;
        else if(start_x < 0)
            start_x = 0;
        cube->mouse_sens = ((cube->menu.settings.mouse_sens.max_sens - cube->menu.settings.mouse_sens.min_sens) * (start_x / (double)(cube->menu.settings.mouse_sens.slider_end_x - cube->menu.settings.mouse_sens.slider_start_x))) + cube->menu.settings.mouse_sens.min_sens;
    }
    ft_renderer(cube, cube->menu.settings.mouse_sens.slider_2, start_x, 0);
}

void ft_crosshair_color(t_cube *cube){
    int mouse_x;
    int mouse_y;
    uint32_t *prev = (uint32_t *)cube->image->pixels;
    mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
    if(mouse_x > cube->menu.settings.crosshair.start_x && mouse_x < cube->menu.settings.crosshair.end_x
     && mouse_y > cube->menu.settings.crosshair.start_y && mouse_y < cube->menu.settings.crosshair.end_y)
    {
        int start_x = mouse_x + (0.01 * (double)cube->screen_width_buff);
        int start_y = mouse_y - (0.06 * (double)cube->screen_height_buff);
        int end_x = start_x + (0.05 * (double)cube->screen_width_buff);
        int end_y = start_y + (0.064 * (double)cube->screen_height_buff);
        int x = start_x + (0.1 * (end_x - start_x));
        int y = start_y + (0.1 * (end_y - start_y));
        int color = prev[mouse_y * cube->screen_width_buff + mouse_x];
        if(mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT))
            cube->menu.settings.crosshair.color = color;

        while(y < end_y){
            x = start_x;
            while(x < end_x){
                prev[y * cube->screen_width_buff + x] = color;
                x++;
            }
            y++;
        }
        ft_renderer(cube, cube->menu.settings.crosshair.border, start_x, start_y);
    }
}
void ft_update_screen_buff(t_cube *cube, mlx_texture_t *texture, int new_w, int new_h){
    if(new_w == cube->screen_width_buff && new_h == cube->screen_height_buff)
        return;
    cube->menu.settings.resolution.texture = texture;
    cube->screen_height_buff = new_h;
    cube->screen_width_buff = new_w;
    cube->screen_height = cube->screen_height_buff / cube->upscaling;
    cube->screen_width = cube->screen_width_buff / cube->upscaling;
    ft_updated_buff_init(cube);
}

void ft_resolution(t_cube *cube){
    int mouse_x;
    int mouse_y;

    mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
    if(cube->menu.settings.mouse_held != RESOLUTION)
        return(ft_renderer(cube, cube->menu.settings.resolution.texture, 0, 0));

    if(mouse_y > cube->menu.settings.resolution.start_y_1080_900 && mouse_y < cube->menu.settings.resolution.end_y_1080_900){

        if(mouse_x > cube->menu.settings.resolution.start_x_1080 && mouse_x < cube->menu.settings.resolution.end_x_1080)
            ft_update_screen_buff(cube, cube->menu.settings.resolution.res_1080_glow, 1920, 1080);

        else if(mouse_x > cube->menu.settings.resolution.start_x_900 && mouse_x < cube->menu.settings.resolution.end_x_900)
            ft_update_screen_buff(cube, cube->menu.settings.resolution.res_900_glow, 1600, 900);

    }
    else if(mouse_y > cube->menu.settings.resolution.start_y_720_480 && mouse_y < cube->menu.settings.resolution.end_y_720_480){

        if(mouse_x > cube->menu.settings.resolution.start_x_720 && mouse_x < cube->menu.settings.resolution.end_x_720)
            ft_update_screen_buff(cube, cube->menu.settings.resolution.res_720_glow, 1280, 720);

        else if(mouse_x > cube->menu.settings.resolution.start_x_480 && mouse_x < cube->menu.settings.resolution.end_x_480)
            ft_update_screen_buff(cube, cube->menu.settings.resolution.res_480_glow, 720, 480);

    }

    ft_renderer(cube, cube->menu.settings.resolution.texture, 0, 0);
}

void ft_update_screen_res(t_cube *cube, int upscale, mlx_texture_t *texture){
    if(upscale == cube->upscaling)
        return;
    cube->menu.settings.upscaling.texture = texture;
    cube->upscaling = upscale;
    cube->screen_height = cube->screen_height_buff / cube->upscaling;
    cube->screen_width = cube->screen_width_buff / cube->upscaling;
    ft_updated_res_init(cube);
}

void ft_upscale(t_cube *cube){
    int mouse_x;
    int mouse_y;

    mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
    if(cube->menu.settings.mouse_held != UPSCALING)
        return(ft_renderer(cube, cube->menu.settings.upscaling.texture, 0, 0));

    if(mouse_y > cube->menu.settings.upscaling.start_y1234 && mouse_y < cube->menu.settings.upscaling.end_y1234){
        if(mouse_x > cube->menu.settings.upscaling.start_x15 && mouse_x < cube->menu.settings.upscaling.end_x15)
            ft_update_screen_res(cube, 1, cube->menu.settings.upscaling.x1_glow);
        else if(mouse_x > cube->menu.settings.upscaling.start_x26 && mouse_x < cube->menu.settings.upscaling.end_x26)
            ft_update_screen_res(cube, 2, cube->menu.settings.upscaling.x2_glow);
        else if(mouse_x > cube->menu.settings.upscaling.start_x37 && mouse_x < cube->menu.settings.upscaling.end_x37)
            ft_update_screen_res(cube, 3, cube->menu.settings.upscaling.x3_glow);
        else if(mouse_x > cube->menu.settings.upscaling.start_x48 && mouse_x < cube->menu.settings.upscaling.end_x48)
            ft_update_screen_res(cube, 4, cube->menu.settings.upscaling.x4_glow);
    }
    else if(mouse_y > cube->menu.settings.upscaling.start_y5678 && mouse_y < cube->menu.settings.upscaling.end_y5678){
        if(mouse_x > cube->menu.settings.upscaling.start_x15 && mouse_x < cube->menu.settings.upscaling.end_x15)
            ft_update_screen_res(cube, 5, cube->menu.settings.upscaling.x5_glow);
        else if(mouse_x > cube->menu.settings.upscaling.start_x26 && mouse_x < cube->menu.settings.upscaling.end_x26)
            ft_update_screen_res(cube, 6, cube->menu.settings.upscaling.x6_glow);
        else if(mouse_x > cube->menu.settings.upscaling.start_x37 && mouse_x < cube->menu.settings.upscaling.end_x37)
            ft_update_screen_res(cube, 7, cube->menu.settings.upscaling.x7_glow);
        else if(mouse_x > cube->menu.settings.upscaling.start_x48 && mouse_x < cube->menu.settings.upscaling.end_x48)
            ft_update_screen_res(cube, 8, cube->menu.settings.upscaling.x8_glow);
    }
    ft_renderer(cube, cube->menu.settings.upscaling.texture, 0, 0);
}

void ft_settings(t_cube *cube){
    int mouse_x;
    int mouse_y;

    mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
    if(cube->menu.settings.mouse_held == NOTHING && mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT)){
        if(mouse_y > (cube->menu.settings.fov.slider_start_y) && mouse_y < (cube->menu.settings.fov.slider_end_y)
         && mouse_x < (cube->menu.settings.fov.slider_end_x) && mouse_x > (cube->menu.settings.fov.slider_start_x))
            cube->menu.settings.mouse_held = FOV_SLIDER;
        else if(mouse_x > cube->menu.settings.resolution.start_x_1080 && mouse_y > cube->menu.settings.resolution.start_y_1080_900
         && mouse_x < cube->menu.settings.resolution.end_x_480 && mouse_y < cube->menu.settings.resolution.end_y_720_480)
            cube->menu.settings.mouse_held = RESOLUTION;
        else if(mouse_y > (cube->menu.settings.mouse_sens.slider_start_y) && mouse_y < (cube->menu.settings.mouse_sens.slider_end_y)
         && mouse_x < (cube->menu.settings.mouse_sens.slider_end_x) && mouse_x > (cube->menu.settings.mouse_sens.slider_start_x))
            cube->menu.settings.mouse_held = MOUSE_SENS_SLIDER;
        else if(mouse_x > cube->menu.settings.upscaling.start_x15 && mouse_x < cube->menu.settings.upscaling.end_x48
         && mouse_y > cube->menu.settings.upscaling.start_y1234 && mouse_y < cube->menu.settings.upscaling.end_y5678)
            cube->menu.settings.mouse_held = UPSCALING;
    }
    if(cube->menu.settings.mouse_held != NOTHING && !mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT)){
        cube->menu.settings.mouse_held = NOTHING;
    }
    ft_fov_slider(cube);
    ft_resolution(cube);
    if(cube->menu.settings.mouse_held == NOTHING || cube->menu.settings.mouse_held == MOUSE_SENS_SLIDER)
        ft_crosshair_color(cube);
    ft_mouse_sens(cube);
    ft_upscale(cube);
    printf("screen_buff : (%d, %d), screen_res : (%d, %d), upscaling : %d\n",cube->screen_width, cube->screen_height, cube->screen_width_buff, cube->screen_height_buff, cube->upscaling);
}

void ft_menu(t_cube *cube){
    
    // int start_x = (cube->screen_width - (cube->menu.title->width)) / 2;
    // int start_y = (cube->screen_height - (cube->menu.title->height)) / 2;
    int start_x = 0;
    int start_y = 0;
    int x = start_x;
    int y = 0;
    int tex_x;
    int tex_y;
    mlx_texture_t   *texture;

    if(cube->menu.state == 0)
        texture = cube->menu.title;
    else
        texture = cube->menu.settings.background;

    double ratio_y = ((double)(texture->height) / (double)(cube->screen_height_buff));
    double ratio_x = ((double)(texture->width) / (double)(cube->screen_width_buff));


    while(y < cube->screen_height_buff){
        x = start_x;
        tex_y = (double)(y) * ratio_y;
        while(x < cube->screen_width_buff){
            tex_x = (double)(x) * ratio_x;
            int pixel_cords = (y * 4 * cube->screen_width_buff) + (x * 4);
            int title_cords = (tex_y * 4 * texture->width) + (tex_x * 4);
            if(tex_x >= texture->width || tex_y >= texture->height || texture->pixels[tex_y * 4 * texture->width + tex_x * 4 + 3] < 127){
                // cube->prev_buffer[(y * 4 * cube->screen_width_buff) + (x * 4) + 0] = 0;
                // cube->prev_buffer[(y * 4 * cube->screen_width_buff) + (x * 4) + 1] = 0;
                // cube->prev_buffer[(y * 4 * cube->screen_width_buff) + (x * 4) + 2] = 0;
                // cube->prev_buffer[(y * 4 * cube->screen_width_buff) + (x * 4) + 3] = 255;
                x++;
                continue;
            }
            cube->image->pixels[pixel_cords + 0] = texture->pixels[title_cords + 0];
            cube->image->pixels[pixel_cords + 1] = texture->pixels[title_cords + 1];
            cube->image->pixels[pixel_cords + 2] = texture->pixels[title_cords + 2];
            cube->image->pixels[pixel_cords + 3] = texture->pixels[title_cords + 3];
            x++;
        }
        y++;
    }
    int mouse_x;
    int mouse_y;

    mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);

    if(cube->menu.state == 1){
        ft_settings(cube);
    if(mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT)
         && ((double)mouse_x > ((double)cube->screen_width_buff * 0.0156) && (double)mouse_x < ((double)cube->screen_width_buff * 0.0468))
         && ((double)mouse_y > ((double)cube->screen_height_buff * 0.0277)) && ((double)mouse_y < (double)cube->screen_height_buff * 0.0833))
            cube->menu.state = 0;
        return;
    }

    if(mlx_is_key_down(cube->mlx, MLX_KEY_ENTER))
        cube->state = GAME;



    // if(mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT) && (mouse_x > (cube->screen_width_buff * 0.86) &&
    //  mouse_x < (cube->screen_width_buff * 0.95)) && (mouse_y > (cube->screen_height_buff * 0.91)) && (mouse_y < cube->screen_height_buff * 0.97))
    if(mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT)
     && ((double)mouse_x > ((double)cube->screen_width_buff * 0.92) && (double)mouse_x < ((double)cube->screen_width_buff * 0.97))
     && ((double)mouse_y > ((double)cube->screen_height_buff * 0.85)) && ((double)mouse_y < (double)cube->screen_height_buff * 0.95))
        cube->menu.state = 1;
}

void ft_draw_enemies(t_cube *cube){

    struct timeval tv;
    gettimeofday(&tv, NULL);
    int i = 0;
    i = 0;
    while(i < ENEMY_NUM){
        int j = i;
        while(j < ENEMY_NUM){
            if(cube->enemy[j].player_dst > cube->enemy[i].player_dst){
                t_enemy tmp = cube->enemy[i];
                cube->enemy[i] = cube->enemy[j];
                cube->enemy[j] = tmp;
            }
            j++;
        }
        i++;
    }
    i = 0;


    if(cube->player.delay == true){
        if((int)(tv.tv_sec - cube->player.atk_time) >= cube->player.weapon.fire_rate)
            cube->player.delay = false;
    }

    while(i < ENEMY_NUM){
        if(is_looking(cube, &cube->enemy[ENEMY_NUM - 1 - i]) && (cube->enemy[ENEMY_NUM - 1 - i].start_y < (cube->screen_height / 2)) &&
                (cube->enemy[ENEMY_NUM - 1 - i].end_y > (cube->screen_height / 2)))
        if(cube->player.delay == true && cube->player.attacked == true){
            if(is_looking(cube, &cube->enemy[ENEMY_NUM - 1 - i]) && (cube->enemy[ENEMY_NUM - 1 - i].start_y < (cube->screen_height / 2)) &&
                (cube->enemy[ENEMY_NUM - 1 - i].end_y > (cube->screen_height / 2)) && (cube->enemy[ENEMY_NUM - 1 - i].player_dst < cube->rays[cube->res / 2].length)){
                    printf("enemy %d attacked! enemy HP: %d\n", ENEMY_NUM - 1 - i, cube->enemy[ENEMY_NUM - 1 - i].HP);
                    cube->enemy[ENEMY_NUM - 1 - i].HP -= cube->player.weapon.DMG;                                  
                }
        }

        ft_enemy(cube, &cube->enemy[i], cube->texture4);
        i++;
    }
}

void ft_draw_proj(t_cube *cube){
    int i = 0;
    while(i < MAX_PROJECTILES){
        if(cube->projectiles[i].in_use == 1)
            ft_projectile(cube, &cube->projectiles[i]);
        i++;
    }
}

void ft_tilt(t_cube *cube){
    int x;
    int y;
    int max_new_x;
    int max_new_y;
    double prev_x;
    double prev_y;
    double offset;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

    max_new_x = cube->screen_width - (cube->tilt_addition_width * 2);
    max_new_y = cube->screen_height - (cube->tilt_addition_height * 2);

    if(!cube->flash.flashed && (cube->player.delay == true || cube->player.hit == true)){
        if(cube->player.delay == true){
            cube->flash.r = 2.0;
            cube->flash.g = 2.0;
            cube->flash.b = 2.0;
        }
        else{
            cube->flash.r = 3.0;
            cube->flash.g = 0.2;
            cube->flash.b = 0.2;
        }
        cube->flash.flashed = true;
        cube->player.hit = false;
    }

    if(cube->flash.flashed && cube->player.delay == false)
        cube->flash.flashed = false;

    printf("r : %lf, g : %lf, b : %lf\n", cube->flash.r, cube->flash.g, cube->flash.b);

    cube->flash.r = ft_lerp_fov(cube->flash.dst_r, cube->flash.r, FLASH_LERP);
    cube->flash.g = ft_lerp_fov(cube->flash.dst_g, cube->flash.g, FLASH_LERP);
    cube->flash.b = ft_lerp_fov(cube->flash.dst_b, cube->flash.b, FLASH_LERP);

    x = 0;
    while(x < max_new_x){
        y = 0;
        prev_x = (double)x + cube->tilt_addition_width;
        offset = (prev_x - (cube->screen_width / 2.0)) * cube->shear_factor; 
        while(y < max_new_y){
            prev_y = ((double)y + cube->tilt_addition_height) + offset;
            if(prev_y >= 0 && prev_y < cube->screen_height){
                int new_dst = (max_new_x * y * 4) + (x * 4);
                int prev_dst = (cube->screen_width * (int)prev_y * 4) + ((int)prev_x * 4);
                cube->new_buffer[new_dst + 0] = (uint8_t)cube->prev_buffer[prev_dst + 0] * cube->flash.r;
                if((uint8_t)cube->prev_buffer[prev_dst + 0] * cube->flash.r > 255)
                    cube->new_buffer[new_dst + 0] = (uint8_t)255;
                cube->new_buffer[new_dst + 1] = (uint8_t)cube->prev_buffer[prev_dst + 1] * cube->flash.g;
                if((uint8_t)cube->prev_buffer[prev_dst + 1] * cube->flash.g > 255)
                    cube->new_buffer[new_dst + 1] = (uint8_t)255;
                cube->new_buffer[new_dst + 2] = (uint8_t)cube->prev_buffer[prev_dst + 2] * cube->flash.b;
                if((uint8_t)cube->prev_buffer[prev_dst + 2] * cube->flash.b > 255)
                    cube->new_buffer[new_dst + 2] = (uint8_t)255;
                cube->new_buffer[new_dst + 3] = (uint8_t)cube->prev_buffer[prev_dst + 3];
            }
            y++;
        }
        x++;
    }
}

// dst_y = abs(dst_y);
// int i = 0;
// int start_j = cube->screen_height - 1 - dst_y;
// int j = start_j;
// while(i < cube->screen_width){
//     j = cube->screen_height - 1 - dst_y;
//     while(j < cube->screen_height){
//         cube->prev_buffer[(cube->screen_width * (int)j * 4) + ((int)i * 4) + 0] = 0;
//         cube->prev_buffer[(cube->screen_width * (int)j * 4) + ((int)i * 4) + 1] = 0;
//         cube->prev_buffer[(cube->screen_width * (int)j * 4) + ((int)i * 4) + 2] = 0;
//         cube->prev_buffer[(cube->screen_width * (int)j * 4) + ((int)i * 4) + 3] = 255;
//         cube->prev_buffer[(cube->screen_width * (int)(j - start_j) * 4) + ((int)i * 4) + 0] = 0;
//         cube->prev_buffer[(cube->screen_width * (int)(j - start_j) * 4) + ((int)i * 4) + 1] = 0;
//         cube->prev_buffer[(cube->screen_width * (int)(j - start_j) * 4) + ((int)i * 4) + 2] = 0;
//         cube->prev_buffer[(cube->screen_width * (int)(j - start_j) * 4) + ((int)i * 4) + 3] = 255;
//         j++;
//     }
//     i++;
// }

void ft_heart(t_cube *cube){
    if((double)cube->player.HP > (0.8 * (double)MAX_HP))
        return ((void)(cube->heart.blur_lerp = BLUR_LERP));
    else if((double)cube->player.HP > (0.6 * (double)MAX_HP) && (double)cube->player.HP <= (0.8 * (double)MAX_HP))
{
    ft_prev_renderer(cube, cube->heart.frame_1, 0, 0);
    cube->heart.blur_lerp = 0.4;
}
    else if((double)cube->player.HP > (0.4 * (double)MAX_HP) && (double)cube->player.HP <= (0.6 * (double)MAX_HP))
{
    ft_prev_renderer(cube, cube->heart.frame_2, 0, 0);
    cube->heart.blur_lerp = 0.3;
}
    else if((double)cube->player.HP > (0.2 * (double)MAX_HP) && (double)cube->player.HP <= (0.4 * (double)MAX_HP))
{
    ft_prev_renderer(cube, cube->heart.frame_3, 0, 0);
    cube->heart.blur_lerp = 0.2;
}
else
{
    ft_prev_renderer(cube, cube->heart.frame_4, 0, 0);
    cube->heart.blur_lerp = 0.1;
}
}

void ft_weapon(t_cube *cube){
    int start_x = cube->screen_width * 0.1;
    int start_y = (cube->screen_height * 0.1);
    // int start_x = 0;
    // int start_y = 0;
    int x = start_x;
    int y = start_y;

    struct timeval tv;
    gettimeofday(&tv, NULL);
    long current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

// printf("pitch_changed : %d, delay : %d\n", cube->player.weapon.pitch_changed, cube->player.delay);


// code for 2nd idle frame
    // if(cube->player.delay == false){
    //     if(current_time - cube->player.weapon.idle_time > 500){
    //         cube->player.weapon.idle_frame = !cube->player.weapon.idle_frame;   
    //         cube->player.weapon.idle_time = current_time;
    //     }
    //     if(cube->player.weapon.idle_frame == 0)
    //         cube->player.weapon.texture = cube->player.weapon.idle_texture;
    //     else
    //         cube->player.weapon.texture = cube->player.weapon.idle_texture_2;
    // }

    if(cube->player.attacked == true){
        // cube->pitch += 10;
        // cube->player.weapon.pitch_dst = cube->pitch + 10;
        printf("THE PLAYER WAS ATTACKED!!!!\n");
        cube->player.weapon.pitch_changed = true;
        cube->player.weapon.pitch_back = false;
        cube->player.weapon.pitch_og = cube->pitch;
        cube->player.weapon.pitch_dst = cube->pitch + cube->player.weapon.pitch_increase;
        cube->fov += (0.2 * cube->init_fov);
        if(cube->fov > 170)
            cube->fov = 170;
        cube->player.weapon.texture = cube->player.weapon.shoot_texture;
        cube->player.weapon.frame_delay = current_time;
        cube->player.weapon.delay = true;
        cube->player.attacked = false;
    }

    if(cube->player.weapon.pitch_changed){
        // cube->pitch += ft_lerp_fov(cube->player.weapon.pitch_dst, cube->pitch, RECOIL_LERP);
        // printf("here\n");
    
        if(!cube->player.weapon.pitch_back){
            cube->pitch += cube->player.weapon.pitch_increase * 4.0;
            cube->player.weapon.pitch_increased += cube->player.weapon.pitch_increase * 4.0;
            if(cube->player.weapon.pitch_increased >= MAX_RECOIL){
                cube->player.weapon.pitch_increased = 0;
                cube->player.weapon.pitch_dst = cube->player.weapon.pitch_og;
                cube->player.weapon.pitch_back = true;
            }
            // printf("top done!\n");
        }

        if(cube->player.weapon.pitch_back){
            cube->pitch -= cube->player.weapon.pitch_increase;
            cube->player.weapon.pitch_increased += cube->player.weapon.pitch_increase;
            if(cube->player.weapon.pitch_increased >= MAX_RECOIL){
                cube->player.weapon.pitch_increased = 0;
                // cube->pitch = cube->player.weapon.pitch_og;
                cube->player.weapon.pitch_changed = false;
            }
            // printf("bottom done!\n");
        }
    }

    // if((cube->player.weapon.pitch_changed == true) && (cube->pitch < cube->player.weapon.pitch_og + cube->player.weapon.pitch_increase))
    //     cube->pitch = ft_lerp_fov(cube->player.weapon.pitch_og + cube->player.weapon.pitch_increase, cube->pitch, RECOIL_LERP);
    // else
    //     cube->player.weapon.pitch_back = true;

    // if((cube->player.weapon.pitch_back == true) && cube->pitch > cube->player.weapon.pitch_og)
    //     cube->pitch = ft_lerp_fov(cube->player.weapon.pitch_og, cube->pitch, RECOIL_LERP);
    // else
    //     cube->player.weapon.pitch_back = false;

    while(y < cube->screen_height){
        x = start_x;
        int tex_y = (double)(y - start_y) * ((double)(cube->player.weapon.texture->height) / (double)((cube->screen_height + cube->player.weapon.move_lerp)));
        while(x < cube->screen_width){
            
            int tex_x = (double)(x - start_x) * ((double)(cube->player.weapon.texture->width) / (double)(cube->screen_width - start_x));
            int prev_cords = ((int)(y) * 4 * cube->screen_width) + ((int)x * 4);
            int weapon_cords = tex_y * 4 * cube->player.weapon.texture->width + tex_x * 4;
            if(tex_x >= cube->player.weapon.texture->width || tex_y >= cube->player.weapon.texture->height || cube->player.weapon.texture->pixels[weapon_cords + 3] == 0){
                x++;
                continue;
            }
            // if(y + cube->player.weapon.move_lerp < cube->screen_height){
                cube->prev_buffer[prev_cords + 0] = cube->player.weapon.texture->pixels[weapon_cords + 0];
                cube->prev_buffer[prev_cords + 1] = cube->player.weapon.texture->pixels[weapon_cords + 1];
                cube->prev_buffer[prev_cords + 2] = cube->player.weapon.texture->pixels[weapon_cords + 2];
                cube->prev_buffer[prev_cords + 3] = cube->player.weapon.texture->pixels[weapon_cords + 3];
            // }
            x++;
        }
        y++;
    }

    int time = (int)(current_time - cube->player.weapon.frame_delay);

    if(cube->player.delay == true){
        if(time >= 150 && time <= 500)
            cube->player.weapon.texture = cube->player.weapon.idle_texture;
        else if(time > 500 && time <= 800)
            cube->player.weapon.texture = cube->player.weapon.pump_texture;
        else if(time > 800 && time <= 900){
            cube->player.weapon.texture = cube->player.weapon.idle_texture;
            cube->player.delay = false;
        }
    }
    // printf("delay : %d, attacked : %d\n", cube->player.delay, cube->player.attacked);
}

void ft_fov_mod(t_cube *cube){
    if(cube->fov != cube->prev_fov){
        cube->proj_dst = (cube->screen_width / 2.0) / tan((cube->fov / 2.0) * RADIANT_RATE); // performance increase possible here
        cube->half_fov_rad = tan((cube->fov / 2.0) * RADIANT_RATE);
        cube->prev_fov = cube->fov;
        cube->mod_rate = (cube->fov * RADIANT_RATE) / cube->res;
    }
    
    cube->fov = ft_lerp_fov(cube->init_fov, cube->fov, FOV_LERP);
}

void ft_game(t_cube *cube){
    ft_mouvement(cube);
    ft_draw_rays(cube);
    ft_floor_ceiling(cube);
    ft_draw_world(cube);
    ft_draw_enemies(cube);
    ft_draw_proj(cube);
    ft_weapon(cube);
    ft_heart(cube);
    ft_fov_mod(cube);
    if(cube->player.HP == 0)
        cube->state = DIED;
}

void ft_died(t_cube *cube){
    int x = 0;
    int y = 0;
    double i = 0;
    double j = 0;
    double i_iter = (double)cube->texture_died->width / (double)cube->screen_width;
    double j_iter = (double)cube->texture_died->height / (double)cube->screen_height;

    while(x < cube->screen_width){
        y = 0;
        j = 0;
        while(y < cube->screen_height){
            if((int)i >= (int)cube->texture_died->width) i = cube->texture_died->width - 1;
            if((int)j >= (int)cube->texture_died->height) j = cube->texture_died->height - 1;
            cube->prev_buffer[(y * 4 * cube->screen_width) + (x * 4) + 0] = cube->texture_died->pixels[(int)(((int)j * cube->texture_died->bytes_per_pixel * cube->texture_died->width) + ((int)i * cube->texture_died->bytes_per_pixel) + 0)];
            cube->prev_buffer[(y * 4 * cube->screen_width) + (x * 4) + 1] = cube->texture_died->pixels[(int)(((int)j * cube->texture_died->bytes_per_pixel * cube->texture_died->width) + ((int)i * cube->texture_died->bytes_per_pixel) + 1)];
            cube->prev_buffer[(y * 4 * cube->screen_width) + (x * 4) + 2] = cube->texture_died->pixels[(int)(((int)j * cube->texture_died->bytes_per_pixel * cube->texture_died->width) + ((int)i * cube->texture_died->bytes_per_pixel) + 2)];
            cube->prev_buffer[(y * 4 * cube->screen_width) + (x * 4) + 3] = cube->texture_died->pixels[(int)(((int)j * cube->texture_died->bytes_per_pixel * cube->texture_died->width) + ((int)i * cube->texture_died->bytes_per_pixel) + 3)];
            y++;
            j += j_iter;
        }
        i += i_iter;
        x++;
    }
}

void state_transition(t_cube *cube, t_state dest){
    if(dest == GAME){
        mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_DISABLED);
        mlx_image_to_window(cube->mlx, cube->image, 0, 0);
        cube->prev_state = GAME;
    }
    else if(dest == DIED){
        mlx_image_to_window(cube->mlx, cube->image_death, 0, 0);
        cube->prev_state = DIED;
    }
    else if(dest == MENU){
        cube->prev_state = MENU;
        mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_NORMAL);
        // clear_image(cube);
    }
}

void state_machine(t_cube *cube){
    if(cube->state == MENU){
        ft_menu(cube);
        // ft_upscaling(cube, cube->image);
    }   
    else if(cube->state == GAME){
        int i = 0;
        while(i < cube->screen_height * cube->screen_width * 4){
            cube->lerp_buffer[i] = cube->prev_buffer[i];
            i++;
        }
        ft_game(cube);
        i = 0;
        while(i < cube->screen_height * cube->screen_width * 4){
            cube->prev_buffer[i] = ft_lerp_pixels(cube->prev_buffer[i], cube->lerp_buffer[i], cube->heart.blur_lerp);
            i++;
        }
        ft_tilt(cube);
        ft_upscaling(cube, cube->image);
        draw_crosshair(cube);
    }
    else if(cube->state == DIED){
        ft_died(cube);
        ft_upscaling(cube, cube->image_death);
    }
}


void ft_update(void *param)
{
    t_cube *cube;
    struct timeval tv;

    cube = (t_cube *)param;
    // cube->grain = !cube->grain;
    // clear_image(cube);
    // ft_rectangle(cube, (t_vect2){0, 0, 0, 0}, (t_vect2){cube->screen_width, cube->screen_height / 2, 0, 0}, 0x000000ff);
    // ft_rectangle(cube, (t_vect2){0, cube->screen_height / 2, 0, 0}, (t_vect2){cube->screen_width, cube->screen_height, 0, 0}, 0x57493eff);
    // draw_grid(cube);
    // draw_player(cub/e);
    gettimeofday(&tv, NULL);
 

    if(cube->state != cube->prev_state)
        state_transition(cube, cube->state);
    state_machine(cube);
    // ft_ray_init(cube, &cube->player.ray, cube->player.angle);
    // ft_draw_rays(cube);
    // ft_ceiling(cube);
    // ft_floor(cube);
    // ft_floor_ceiling(cube);
    // ft_draw_world(cube);
    // ft_enemy(cube, &cube->enemy, cube->texture4);
    // ft_enemy(cube, &cube->enemy2, cube->texture5);
    // ft_enemy(cube, &cube->enemy3, cube->texture6);
    // ft_upscaling(cube, cube->image);
    // draw_crosshair(cube);
    cube->final_t = tv.tv_sec;
    // printf("before mouvement pitch : %lf\n", cube->pitch);
    // ft_mouvement(cube);
    // printf("after mouvement pitch : %lf\n", cube->pitch);
    cube->fps++;
    if(cube->final_t - cube->init_t == 1)
    {
        printf("fps : %d, player HP : %d\n", cube->fps, cube->player.HP);
        cube->init_t = cube->final_t;
        cube->fps = 0;
    }
    // ft_shader(cube);
    // ft_crt_vhs_effect(cube);
}

void ft_parse(t_cube *cube)
{
    int i = 0;
    int j = 0;
    while(i < 10)
    {
        j = 0;
        while(j < 10)
        {
            printf("i : %d, j : %d, value : %d\n", i, j, cube->map[i][j]);
            j++;
        }
        i++;
    }
}

static const int g_map_template[MAP_Y][MAP_X] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void ft_map_init(t_cube *cube)
{
    cube->map = ft_calloc(MAP_Y + 1, sizeof(char *));
    cube->floor_map = ft_calloc(MAP_Y + 1, sizeof(char *));
    if (cube->map == NULL)
    {
        mlx_terminate(cube->mlx);
        perror("Alloc error : ");
        exit(EXIT_FAILURE);
    }
    if (cube->floor_map == NULL)
    {
        mlx_terminate(cube->mlx);
        perror("Alloc error : ");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (i < MAP_Y)
    {
        cube->map[i] = ft_calloc(MAP_X + 1, sizeof(char));
        if (cube->map[i] == NULL)
        {
            mlx_terminate(cube->mlx);
            perror("Alloc error : ");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    int y = 0;
    while (y < MAP_Y)
    {
        int x = 0;
        while (x < MAP_X)
        {
            cube->map[y][x] = (char)g_map_template[y][x];
            x++;
        }
        y++;
    }
}

void ft_init_enemies(t_cube *cube){
    int i = 0;
    struct timeval tv;
    unsigned long seed;

    gettimeofday(&tv, NULL);
    seed = (unsigned long)tv.tv_usec / 100;

    while(i < ENEMY_NUM){
        cube->enemy[i].HP = 100;
        cube->enemy[i].blood_frame_index = 0;
        cube->enemy[i].dead = false;
        cube->enemy[i].delay = false;
        cube->enemy[i].atk_delay = 1;
        cube->enemy[i].DMG = 20;
        cube->enemy[i].hitbox_len = 50; // COMEBACK TO THIS ITS VERY IMPORTANT, THE HITBOX NEEDS TO SCALE WITH THE ENEMY DISTANCE FROM PLAYER EACH FRAME
        int posX = (int)(ft_rand(&seed) % (int)(MAP_X * GRID_SIZE));
        int posY = (int)(ft_rand(&seed) % (int)(MAP_Y * GRID_SIZE));
        // printf("1 : posX : %d, posY : %d\n", posX, posY);
        while(cube->map[(int)(posY / GRID_SIZE)][(int)(posX / GRID_SIZE)] == 1 || (posX >= (MAP_X * GRID_SIZE) || posY >= (MAP_Y * GRID_SIZE))){
            posX = (int)(ft_rand(&seed) % (int)(MAP_X * GRID_SIZE));
            posY = (int)(ft_rand(&seed) % (int)(MAP_Y * GRID_SIZE));
            // printf("2 : posX : %d, posY : %d\n", posX, posY);
        }
        cube->enemy[i].x = (posX);
        cube->enemy[i].y = (posY);
        // printf("pos[%d] : (%d, %d)\n", i, (posX), (posY));
        // printf("updated\n");
        cube->enemy[i].player_dst = sqrt((cube->player.x - cube->enemy[i].x) * (cube->player.x - cube->enemy[i].x) + (cube->player.y - cube->enemy[i].y) * (cube->player.y - cube->enemy[i].y));
        cube->enemy[i].max_hit_angle = atan2((cube->enemy[i].hitbox_len / 2.0), cube->enemy[i].player_dst);
        i++;
    }
}

// void ft_init_audio(t_cube *cube){
//     ma_uint64 length;
//     ma_uint64 now;

//     cube->audio = ft_calloc(1, sizeof(t_audio));
//     if(ma_engine_init(NULL, &cube->audio->engine) != MA_SUCCESS){
//         printf("failed to init audio engine :(\n");
//         exit(1);
//     }
//     ma_sound_init_from_file(&cube->audio->engine, "/home/skully/work/mac/Psychosis_start.wav", 0, NULL, NULL, &cube->audio->bg_start);
//     ma_sound_init_from_file(&cube->audio->engine, "/home/skully/work/mac/Psychosis_loop.wav", 0, NULL, NULL, &cube->audio->bg_loop);
//     ma_sound_set_looping(&cube->audio->bg_loop, MA_TRUE);
//     ma_sound_get_length_in_pcm_frames(&cube->audio->bg_start, &length);
//     now = ma_engine_get_time_in_pcm_frames(&cube->audio->engine);
//     ma_sound_set_start_time_in_pcm_frames(&cube->audio->bg_start, now);
//     ma_sound_start(&cube->audio->bg_start);
//     ma_sound_set_start_time_in_pcm_frames(&cube->audio->bg_loop, now + length + 5);
//     ma_sound_start(&cube->audio->bg_loop);
// }

void ft_updated_res_init(t_cube *cube){
    cube->res = cube->screen_width;
    cube->tilt_addition_height = fabs(cube->shear_factor) * cube->screen_height;
    cube->tilt_addition_width = fabs(cube->shear_factor) * cube->screen_width;
    cube->move_increase = 0.05 * cube->screen_height;
    cube->pitch_max = cube->screen_height + 100;
    free(cube->prev_buffer);
    free(cube->new_buffer);
    free(cube->lerp_buffer);
    free(cube->z_buffer);
    free(cube->rays);
    cube->prev_buffer = ft_calloc(cube->screen_height * cube->screen_width, 4);
    cube->new_buffer = ft_calloc((cube->screen_height - cube->tilt_addition_height) * (cube->screen_width - cube->tilt_addition_width), 4);
    cube->lerp_buffer = ft_calloc(cube->screen_height * cube->screen_width, 4);
    cube->rays = ft_calloc(cube->res + 1, sizeof(t_ray));
    cube->z_buffer = ft_calloc(cube->screen_width + 1, sizeof(double));
    cube->proj_dst = (cube->screen_width / 2.0) / tan((cube->fov / 2.0) * RADIANT_RATE);
    cube->line_girth = (int)(cube->screen_width / cube->res);
    cube->mod_rate = (cube->fov * RADIANT_RATE) / cube->res;
    clear_image(cube);
}

void ft_updated_buff_init(t_cube *cube){
    mlx_resize_image(cube->image, cube->screen_width_buff, cube->screen_height_buff);
    mlx_resize_image(cube->image_death, cube->screen_width_buff, cube->screen_height_buff);
    mlx_set_window_size(cube->mlx, cube->screen_width_buff, cube->screen_height_buff);
    // mlx_image_to_window(cube->mlx, cube->image, 0, 0);
    cube->menu.settings.upscaling.start_y1234 = 0.78 * cube->screen_height_buff;
    cube->menu.settings.upscaling.end_y1234 = 0.807 * cube->screen_height_buff;
    cube->menu.settings.upscaling.start_y5678 = 0.873 * cube->screen_height_buff;
    cube->menu.settings.upscaling.end_y5678 = 0.9 * cube->screen_height_buff;    
    cube->menu.settings.fov.slider_start_y = 0.20 * cube->screen_height_buff;
    cube->menu.settings.fov.slider_end_y = 0.24 * cube->screen_height_buff;
    cube->menu.settings.mouse_sens.slider_start_y = 0.78 * cube->screen_height_buff;
    cube->menu.settings.mouse_sens.slider_end_y = 0.81 * cube->screen_height_buff;
    cube->menu.settings.resolution.start_y_1080_900 = 0.48 * cube->screen_height_buff;
    cube->menu.settings.resolution.end_y_1080_900 = 0.51 * cube->screen_height_buff;
    cube->menu.settings.resolution.start_y_720_480 = 0.59 * cube->screen_height_buff;
    cube->menu.settings.resolution.end_y_720_480 = 0.62 * cube->screen_height_buff;
    cube->menu.settings.crosshair.start_y = 0.178 * cube->screen_height_buff;
    cube->menu.settings.crosshair.end_y = 0.58 * cube->screen_height_buff;
    cube->crosshair_hori_start = (t_vect2){(cube->screen_width_buff / 2) - CROSSHAIR_LEN, (cube->screen_height_buff / 2) - CROSSHAIR_GIRTH, 0, 0};
    cube->crosshair_hori_end = (t_vect2){(cube->screen_width_buff / 2) + CROSSHAIR_LEN, (cube->screen_height_buff / 2) + CROSSHAIR_GIRTH, 0, 0};
    cube->crosshair_vert_start = (t_vect2){(cube->screen_width_buff / 2) - CROSSHAIR_GIRTH, (cube->screen_height_buff / 2) - CROSSHAIR_LEN, 0, 0};
    cube->crosshair_vert_end = (t_vect2){(cube->screen_width_buff / 2) + CROSSHAIR_GIRTH, (cube->screen_height_buff / 2) + CROSSHAIR_LEN, 0, 0};
    cube->menu.settings.upscaling.start_x15 = 0.089 * cube->screen_width_buff;
    cube->menu.settings.upscaling.end_x15 = 0.11 * cube->screen_width_buff;
    cube->menu.settings.upscaling.start_x26 = 0.162 * cube->screen_width_buff;
    cube->menu.settings.upscaling.end_x26 = 0.183 * cube->screen_width_buff;
    cube->menu.settings.upscaling.start_x37 = 0.235 * cube->screen_width_buff;
    cube->menu.settings.upscaling.end_x37 = 0.256 * cube->screen_width_buff;
    cube->menu.settings.upscaling.start_x48 = 0.310 * cube->screen_width_buff;
    cube->menu.settings.upscaling.end_x48 = 0.331 * cube->screen_width_buff;
    cube->menu.settings.fov.slider_start_x = 0.065 * cube->screen_width_buff;
    cube->menu.settings.fov.slider_end_x = 0.354 * cube->screen_width_buff;
    cube->menu.settings.mouse_sens.slider_start_x = 0.605 * cube->screen_width_buff;
    cube->menu.settings.mouse_sens.slider_end_x = 0.895 * cube->screen_width_buff;
    cube->menu.settings.resolution.start_x_1080 = 0.055 * cube->screen_width_buff;
    cube->menu.settings.resolution.end_x_1080 = 0.175 * cube->screen_width_buff;
    cube->menu.settings.resolution.start_x_900 = 0.245 * cube->screen_width_buff;
    cube->menu.settings.resolution.end_x_900 = 0.358 * cube->screen_width_buff;
    cube->menu.settings.resolution.start_x_720 = 0.057 * cube->screen_width_buff;
    cube->menu.settings.resolution.end_x_720 = 0.173 * cube->screen_width_buff;
    cube->menu.settings.resolution.start_x_480 = 0.265 * cube->screen_width_buff;
    cube->menu.settings.resolution.end_x_480 = 0.365 * cube->screen_width_buff;
    cube->menu.settings.crosshair.start_x = 0.636 * cube->screen_width_buff;
    cube->menu.settings.crosshair.end_x = 0.865 * cube->screen_width_buff;
    ft_updated_res_init(cube);
}


void ft_init(t_cube *cube)
{
    struct timeval tv;

    // ft_init_audio(cube);
    gettimeofday(&tv, NULL);
    cube->upscaling = UPSCALING_RATE;
    cube->screen_height_buff = SCREEN_HEIGHT_BUFF;
    cube->screen_width_buff = SCREEN_WIDTH_BUFF;
    cube->screen_height = (double)cube->screen_height_buff / (double)cube->upscaling;
    cube->screen_width = (double)cube->screen_width_buff / (double)cube->upscaling;
    cube->res = cube->screen_width;
    cube->move_increase = 0.05 * (double)cube->screen_height;
    cube->pitch_max = (double)cube->screen_height * 1.1;
    cube->init_fov = FOV;
    cube->fov = cube->init_fov;
    cube->prev_fov = cube->init_fov;
    cube->mouse_sens = TURN_SPEED;
    cube->proj_dst = ((double)cube->screen_width / 2.0) / tan(((double)cube->fov / 2.0) * RADIANT_RATE);
    cube->half_fov_rad = tan(((double)cube->fov / 2.0) * RADIANT_RATE);
    cube->player.x = GRID_SIZE + (GRID_SIZE / 2);
    cube->player.y = GRID_SIZE + (GRID_SIZE / 2);
    cube->player.HP = MAX_HP;
    cube->player.delay = false;
    cube->player.atk_delay = 1;
    cube->player.DMG = 50;
    cube->player.current_speed_LR_X = 0.0;
    cube->player.current_speed_LR_Y = 0.0;
    cube->player.current_speed_FB_X = 0.0;
    cube->player.current_speed_FB_Y = 0.0;
    cube->player.last_FB = UP;
    cube->player.last_LR = LEFT;
    cube->player.attacked = false;
    cube->player.hit = false;
    cube->state = MENU;
    cube->prev_state = MENU;

    cube->menu.title = mlx_load_png("./menu_screen_1.png");
    cube->menu.settings.background = mlx_load_png("./settings_assets/settings_background.png");
    cube->menu.settings.fov.bar_1 = mlx_load_png("./settings_assets/bar_1.png");
    cube->menu.settings.bar_2 = mlx_load_png("./settings_assets/bar_2.png");
    cube->menu.settings.fov.slider_1 = mlx_load_png("./settings_assets/slider_1.png");
    cube->menu.settings.slider_2 = mlx_load_png("./settings_assets/slider_2.png");

    cube->menu.settings.upscaling.x1_glow = mlx_load_png("./settings_assets/x1_glow.png");
    cube->menu.settings.upscaling.x2_glow = mlx_load_png("./settings_assets/x2_glow.png");
    cube->menu.settings.upscaling.x3_glow = mlx_load_png("./settings_assets/x3_glow.png");
    cube->menu.settings.upscaling.x4_glow = mlx_load_png("./settings_assets/x4_glow.png");
    cube->menu.settings.upscaling.x5_glow = mlx_load_png("./settings_assets/x5_glow.png");
    cube->menu.settings.upscaling.x6_glow = mlx_load_png("./settings_assets/x6_glow.png");
    cube->menu.settings.upscaling.x7_glow = mlx_load_png("./settings_assets/x7_glow.png");
    cube->menu.settings.upscaling.x8_glow = mlx_load_png("./settings_assets/x8_glow.png");
    cube->menu.settings.upscaling.start_x15 = 0.089 * cube->screen_width_buff;
    cube->menu.settings.upscaling.end_x15 = 0.11 * cube->screen_width_buff;
    cube->menu.settings.upscaling.start_x26 = 0.162 * cube->screen_width_buff;
    cube->menu.settings.upscaling.end_x26 = 0.183 * cube->screen_width_buff;
    cube->menu.settings.upscaling.start_x37 = 0.235 * cube->screen_width_buff;
    cube->menu.settings.upscaling.end_x37 = 0.256 * cube->screen_width_buff;
    cube->menu.settings.upscaling.start_x48 = 0.310 * cube->screen_width_buff;
    cube->menu.settings.upscaling.end_x48 = 0.331 * cube->screen_width_buff;
    cube->menu.settings.upscaling.start_y1234 = 0.78 * cube->screen_height_buff;
    cube->menu.settings.upscaling.end_y1234 = 0.807 * cube->screen_height_buff;
    cube->menu.settings.upscaling.start_y5678 = 0.873 * cube->screen_height_buff;
    cube->menu.settings.upscaling.end_y5678 = 0.9 * cube->screen_height_buff;
    if(cube->upscaling == 1)
        cube->menu.settings.upscaling.texture = cube->menu.settings.upscaling.x1_glow;
    else if(cube->upscaling == 2)
        cube->menu.settings.upscaling.texture = cube->menu.settings.upscaling.x2_glow;
    else if(cube->upscaling == 3)
        cube->menu.settings.upscaling.texture = cube->menu.settings.upscaling.x3_glow;
    else if(cube->upscaling == 4)
        cube->menu.settings.upscaling.texture = cube->menu.settings.upscaling.x4_glow;
    else if(cube->upscaling == 5)
        cube->menu.settings.upscaling.texture = cube->menu.settings.upscaling.x5_glow;
    else if(cube->upscaling == 6)
        cube->menu.settings.upscaling.texture = cube->menu.settings.upscaling.x6_glow;
    else if(cube->upscaling == 7)
        cube->menu.settings.upscaling.texture = cube->menu.settings.upscaling.x7_glow;
    else if(cube->upscaling == 8)
        cube->menu.settings.upscaling.texture = cube->menu.settings.upscaling.x8_glow;

    cube->menu.settings.mouse_held = 0;

    cube->menu.settings.fov.slider_start_y = 0.20 * cube->screen_height_buff;
    cube->menu.settings.fov.slider_end_y = 0.24 * cube->screen_height_buff;
    cube->menu.settings.fov.slider_start_x = 0.065 * cube->screen_width_buff;
    cube->menu.settings.fov.slider_end_x = 0.354 * cube->screen_width_buff;
    cube->menu.settings.fov.min_fov = 30;
    cube->menu.settings.fov.max_fov = 150;

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
    cube->shear_factor = tan(cube->tilt_angle * RADIANT_RATE);
    cube->tilt_addition_height = fabs(cube->shear_factor) * cube->screen_height;
    cube->tilt_addition_width = fabs(cube->shear_factor) * cube->screen_width;

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

    cube->crosshair_hori_start = (t_vect2){(cube->screen_width_buff / 2) - CROSSHAIR_LEN, (cube->screen_height_buff / 2) - CROSSHAIR_GIRTH, 0, 0};
    cube->crosshair_hori_end = (t_vect2){(cube->screen_width_buff / 2) + CROSSHAIR_LEN, (cube->screen_height_buff / 2) + CROSSHAIR_GIRTH, 0, 0};
    cube->crosshair_vert_start = (t_vect2){(cube->screen_width_buff / 2) - CROSSHAIR_GIRTH, (cube->screen_height_buff / 2) - CROSSHAIR_LEN, 0, 0};
    cube->crosshair_vert_end = (t_vect2){(cube->screen_width_buff / 2) + CROSSHAIR_GIRTH, (cube->screen_height_buff / 2) + CROSSHAIR_LEN, 0, 0};
    cube->projectiles = ft_calloc(MAX_PROJECTILES + 1, sizeof(t_projectile));
    cube->prev_buffer = ft_calloc(cube->screen_height * cube->screen_width, 4);
    cube->new_buffer = ft_calloc((cube->screen_height - cube->tilt_addition_height) * (cube->screen_width - cube->tilt_addition_width), 4);
    cube->lerp_buffer = ft_calloc(cube->screen_height * cube->screen_width, 4);
    cube->mod_rate = (cube->fov * RADIANT_RATE) / cube->res;

    cube->fps = 0;
    cube->grain = true;
    cube->pitch = 0.0;
    cube->z_buffer = ft_calloc(cube->screen_width, sizeof(double));
    cube->rays = ft_calloc(cube->res + 1, sizeof(t_ray));
    cube->init_t = tv.tv_sec;
    cube->final_t = tv.tv_sec;
    cube->moving = false;
    cube->enemy = ft_calloc(ENEMY_NUM + 1, sizeof(t_enemy));
    ft_init_enemies(cube);
    cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
    cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
    cube->player.angle = 0;
    cube->texture = mlx_load_png("./s2 Concrete Squares Grey.png");
    cube->texture2 = mlx_load_png("./Tiles_Rectangle_Grey_1.png");
    cube->texture3 = mlx_load_png("./Concrete_02_Grey_1.png");
    cube->texture4 = mlx_load_png("./job_dude.png");
    cube->texture5 = mlx_load_png("./Monster_1.png");
    cube->texture6 = mlx_load_png("./job_app.png");
    cube->texture_died = mlx_load_png("./you_died.png");
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
    if(cube->image_death == NULL)
    {
        mlx_terminate(cube->mlx);
        perror("image init error :");
        exit(EXIT_FAILURE);
    }
    mlx_image_to_window(cube->mlx, cube->image, 0, 0);
    mlx_set_mouse_pos(cube->mlx, cube->screen_width / 2, cube->screen_height / 2);
}

void f(){
    system("leaks -q cub3d");
}

int main()
{
    t_cube cube;
    // atexit(f);
    ft_map_init(&cube);
    // ft_parse(&cube);
    ft_init(&cube);
    mlx_loop_hook(cube.mlx, ft_update, &cube);
    mlx_loop(cube.mlx);
    mlx_terminate(cube.mlx);
    return 0;
}














