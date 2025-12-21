/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:13:24 by skully            #+#    #+#             */
/*   Updated: 2025/12/21 16:46:07 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void clear_image(t_cube *cube)
{
    int buffer_size = SCREEN_HEIGHT * SCREEN_WIDTH * 4;
    ft_memset(cube->image->pixels, 0, buffer_size);
}

void ft_rectangle(t_cube *cube, t_vect2 start_cords, t_vect2 end_cords, int color)
{
    int start_temp;

    start_temp = start_cords.x;
    while(start_cords.y < end_cords.y)
    {
        start_cords.x = start_temp;
        while(start_cords.x < end_cords.x)
        {
            mlx_put_pixel(cube->image, (int)start_cords.x, (int)start_cords.y, color);
            start_cords.x++;
        }
        start_cords.y++;
    }
}

void ft_angle_limit(double *angle)
{
    if(*angle < 0)
        *angle = (2 * PI) + *angle;
    else if(*angle > (PI * 2))
        *angle = *angle - (2 * PI);
}

uint8_t ft_lerp_pixels(uint8_t new, uint8_t old){
    return (new * LERP) + (old * (1.0 - LERP));    
}

void draw_player(t_cube *cube)
{
    int y;
    int x;
    int offset;

    offset = 3;
    if(cube->player.x < offset)
        cube->player.x = offset;
    else if(cube->player.x > SCREEN_WIDTH)
        cube->player.x = SCREEN_WIDTH - offset;
    if(cube->player.y < offset)
        cube->player.y = offset;
    else if(cube->player.y > SCREEN_HEIGHT)
        cube->player.y = SCREEN_HEIGHT - offset;
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

    mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
    mouse_x = mouse_x - (SCREEN_WIDTH / 2);
    mouse_y = mouse_y - (SCREEN_HEIGHT / 2);
    cube->player.angle += mouse_x * TURN_SPEED;
    cube->pitch += (-1 * mouse_y) * (TURN_SPEED * SCREEN_HEIGHT);
    if(cube->pitch > PITCH_MAX)
        cube->pitch = PITCH_MAX;
    if(cube->pitch < -PITCH_MAX)
        cube->pitch = -PITCH_MAX;
    mlx_set_mouse_pos(cube->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void ft_mouvement(t_cube *cube)
{
    ft_angle_limit(&cube->player.angle);
    ft_turn(cube);
    if(mlx_is_key_down(cube->mlx, MLX_KEY_D))
    {
        cube->player.x += -1 * sin(cube->player.angle) * PLAYER_SPEED * cube->mlx->delta_time;
        cube->player.y += cos(cube->player.angle) * PLAYER_SPEED * cube->mlx->delta_time;
        // cube->player.angle += (0.02 * PLAYER_SPEED);
    }
    else if(mlx_is_key_down(cube->mlx, MLX_KEY_A))
    {
        cube->player.x -= -1 * sin(cube->player.angle) * PLAYER_SPEED * cube->mlx->delta_time;
        cube->player.y -= cos(cube->player.angle) * PLAYER_SPEED * cube->mlx->delta_time;
        // cube->player.angle -= (0.02 * PLAYER_SPEED);
    }
    if(mlx_is_key_down(cube->mlx, MLX_KEY_W))
    {
        cube->player.x += cos(cube->player.angle) * PLAYER_SPEED * cube->mlx->delta_time;
        cube->player.y += sin(cube->player.angle) * PLAYER_SPEED * cube->mlx->delta_time;
    }
    else if(mlx_is_key_down(cube->mlx, MLX_KEY_S))
    {
        cube->player.x -= cos(cube->player.angle) * PLAYER_SPEED * cube->mlx->delta_time;
        cube->player.y -= sin(cube->player.angle) * PLAYER_SPEED * cube->mlx->delta_time;
    }
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
    double PlaneX = -DirY * HALF_FOV_RAD;
    double PlaneY =  DirX * HALF_FOV_RAD;

    for (int i = 0; i < RES; i++)
    {
        double cameraX = 2.0 * i / (double)RES - 1.0;

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
//     cube->min_length = 99999999;
//     start_angle = cube->player.angle - ((FOV / 2) * RADIANT_RATE);
//     while(i < RES)
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

bool check_screen_limits(t_vect2 len)
{
    if(len.x >= SCREEN_WIDTH)
        return true;
    else if(len.x < 0)
        return true;
    if(len.y >= SCREEN_HEIGHT)
        return true;
    else if(len.y < 0)
        return true;
    return false;
}

void set_screen_limits(t_vect2 *len)
{
    if(len->x > SCREEN_WIDTH)
        len->x = SCREEN_WIDTH;
    else if(len->x < 0)
        len->x = 0;
    if(len->y > SCREEN_HEIGHT)
        len->y = SCREEN_HEIGHT;
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
    if(check_screen_limits(start) && start.y <= 0)
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
    while(start.y < SCREEN_HEIGHT && start.y < end.y && cords.y < cube->texture->height)
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
        if(!check_screen_limits(start)){
            int k = ((int)cords.x * cube->texture->bytes_per_pixel) + (cube->texture->width * cube->texture->bytes_per_pixel * (int)cords.y);
            cube->prev_buffer[(SCREEN_WIDTH * (int)start.y * 4) + ((int)start.x * 4) + 0] = cube->texture->pixels[k + 0] * (tmp);
            cube->prev_buffer[(SCREEN_WIDTH * (int)start.y * 4) + ((int)start.x * 4) + 1] = cube->texture->pixels[k + 1] * (tmp);
            cube->prev_buffer[(SCREEN_WIDTH * (int)start.y * 4) + ((int)start.x * 4) + 2] = cube->texture->pixels[k + 2] * (tmp);
            cube->prev_buffer[(SCREEN_WIDTH * (int)start.y * 4) + ((int)start.x * 4) + 3] = cube->texture->pixels[k + 3];
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

    start.x = (SCREEN_WIDTH - (cube->line_girth * RES)) / 2;
    ft_rectangle(cube, (t_vect2){0, 0, 0, 0}, (t_vect2){start.x, SCREEN_HEIGHT, 0, 0}, 0x000000ff);
    ft_rectangle(cube, (t_vect2){SCREEN_WIDTH - start.x, 0, 0, 0}, (t_vect2){SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0}, 0x000000ff);
    i = 0;
    while(i <= RES)
    {
        j = 0;
        double length = cube->rays[i].length * cos(cube->rays[i].real_angle - cube->player.angle);
        len = ((GRID_SIZE) / length) * PROJ_DST;
        start.y = ((SCREEN_HEIGHT - len) / 2) + cube->pitch;
        end.x = start.x;
        end.y = start.y + len;
        while(j < cube->line_girth)
        {
            ft_draw_texture(cube, &cube->rays[i], start, end, len);
            start.x++;
            end.x++;
            j++;
        }
        i++;
    }
}

void ft_enemy(t_cube *cube){
    double angle_diff = atan2(cube->enemy.y - cube->player.y, cube->enemy.x - cube->player.x);
    double tetha_delta = angle_diff - cube->player.angle;
    while(tetha_delta > PI)
        tetha_delta -= 2 * PI;
    while(tetha_delta < -PI)
        tetha_delta += 2 * PI;
    
    int midX = ((0.5 * SCREEN_WIDTH)) + (tan(tetha_delta) * PROJ_DST);
    double dst = sqrt((cube->enemy.x - cube->player.x) * (cube->enemy.x - cube->player.x) + (cube->enemy.y - cube->player.y) * (cube->enemy.y - cube->player.y)) * cos(tetha_delta);

    if(dst < 0.1) 
    return;

    double tmp = 1.0 - (dst / MAX_DST);
    if(tmp > 1.0)
        tmp = 1.0;
    else if(tmp < 0.0)
        tmp = 0.0;

    double height = (GRID_SIZE / dst) * PROJ_DST;

    double scale_ratio = cube->texture4->height / height;

    int start_x = midX - (cube->texture4->width / scale_ratio) / 2;
    int start_y = ((SCREEN_HEIGHT / 2.0) + cube->pitch) - (cube->texture4->height / scale_ratio) / 2;
    int const_y = start_y;
    int end_x = start_x + (cube->texture4->width / scale_ratio);
    int end_y = start_y + (cube->texture4->height / scale_ratio);

    double tex_x = 0;
    double tex_y = 0;

    if (start_x < 0) {
        tex_x += (-start_x) * scale_ratio;
        start_x = 0;
    }

    if (start_x >= SCREEN_WIDTH) return;
    if (end_x > SCREEN_WIDTH) end_x = SCREEN_WIDTH;

    if (start_y < 0) {
        tex_y = (-start_y) * scale_ratio;
        start_y = 0;
    }
    if (start_y >= SCREEN_HEIGHT) return;

    if (end_x > SCREEN_WIDTH) end_x = SCREEN_WIDTH;
    if (end_y > SCREEN_HEIGHT) end_y = SCREEN_HEIGHT;

    while(start_x < end_x){
        start_y = const_y;
        int x = (int)tex_x;
        if (x >= (int)cube->texture4->width) x = cube->texture4->width - 1;
        if (x < 0) x = 0;
        tex_y = 0;
        while(start_y < end_y){
            int y = (int)tex_y;
            if (y >= (int)cube->texture4->height) y = cube->texture4->height - 1;
            if (y < 0) y = 0;

            if(!check_screen_limits((t_vect2){start_x, start_y, 0, 0})){
                int k = (x * cube->texture4->bytes_per_pixel) + (cube->texture4->width * cube->texture4->bytes_per_pixel * y);
                if(cube->texture4->pixels[k + 3] > 128){
                    cube->prev_buffer[(SCREEN_WIDTH * (int)start_y * 4) + ((int)start_x * 4) + 0] = cube->texture4->pixels[k + 0] * tmp;
                    cube->prev_buffer[(SCREEN_WIDTH * (int)start_y * 4) + ((int)start_x * 4) + 1] = cube->texture4->pixels[k + 1] * tmp;
                    cube->prev_buffer[(SCREEN_WIDTH * (int)start_y * 4) + ((int)start_x * 4) + 2] = cube->texture4->pixels[k + 2] * tmp;
                    cube->prev_buffer[(SCREEN_WIDTH * (int)start_y * 4) + ((int)start_x * 4) + 3] = cube->texture4->pixels[k + 3];
                }
            }
            start_y++;
            tex_y += scale_ratio;
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
//     if (end_y > SCREEN_HEIGHT) 
//         end_y = SCREEN_HEIGHT;

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
//             pixel_index = (SCREEN_WIDTH * (int)start.y * 4) + ((int)start.x * 4);

//             if (pixel_index >= 0 && pixel_index < SCREEN_WIDTH * SCREEN_HEIGHT * 4)
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
//     double sprite_dir = atan2(cube->enemy.y - cube->player.y, cube->enemy.x - cube->player.x);
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
//     int screen_mid_x = (SCREEN_WIDTH / 2) + (tan(theta_delta) * PROJ_DST);
    
//     int start_x = screen_mid_x - (sprite_width / 2);
//     int end_x   = screen_mid_x + (sprite_width / 2);
//     int start_y = (SCREEN_HEIGHT - sprite_height) / 2;

//     // --- 4. DRAW COLUMNS ---
//     t_vect2 pos;
//     pos.y = start_y;
    
//     int x = start_x;
//     while (x < end_x)
//     {
//         // Only draw if column is within screen bounds
//         if (x >= 0 && x < SCREEN_WIDTH)
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

//     double posZ = 0.5 * SCREEN_HEIGHT; // cameraHeight = 0.5

//     for (int i = SCREEN_HEIGHT / 2; i < SCREEN_HEIGHT; i++)
//     {
//         double p = i - SCREEN_HEIGHT / 2.0;
//         double rowDist = posZ / p;

//         // World positions at left & right
//         double floorXLeft  = playerX + rowDist * (dirX - planeX);
//         double floorYLeft  = playerY + rowDist * (dirY - planeY);
//         double floorXRight = playerX + rowDist * (dirX + planeX);
//         double floorYRight = playerY + rowDist * (dirY + planeY);

//         double stepX = (floorXRight - floorXLeft) / SCREEN_WIDTH;
//         double stepY = (floorYRight - floorYLeft) / SCREEN_WIDTH;

//         double floorX = floorXLeft;
//         double floorY = floorYLeft;

//         for (int j = 0; j < SCREEN_WIDTH; j++)
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
//     while(x < SCREEN_WIDTH)
//     {
//         y = 0;
//         while(y < SCREEN_HEIGHT)
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
//     // double posZ = SCREEN_HEIGHT / 2.0;
//     // double posZ = (CAM_H) * PROJ_DST;
//     double posZ = V_PROJ_DST;
//     int i = posZ + 1;
//     while(i < SCREEN_HEIGHT)
//     {
//         double p = (float)i - SCREEN_HEIGHT / 2.0;   // distance from horizon in screen pixels
//         double rowDst = posZ / p;
//         t_vect2 floorL = (t_vect2){(PlayerPos.x) + rowDst * RayDirL.x, (PlayerPos.y) + rowDst * RayDirL.y, 0, 0};
//         t_vect2 floorR = (t_vect2){(PlayerPos.x) + rowDst * RayDirR.x, (PlayerPos.y) + rowDst * RayDirR.y, 0, 0};

//         t_vect2 step = (t_vect2){(floorR.x - floorL.x) / SCREEN_WIDTH, (floorR.y - floorL.y) / SCREEN_WIDTH, 0, 0};

//         t_vect2 ft_floor = (t_vect2){floorL.x, floorL.y, 0, 0};

//         int j = 0;
//         while(j < SCREEN_WIDTH)
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
    while(i < SCREEN_HEIGHT / 2)
    {
        // if replace SCREEN_HEIGHT with SCREEN_WIDTH you get ceiling textures PS: found it by accident :P
        double p = (SCREEN_HEIGHT / 2.0) - (float)i;   // distance from horizon in screen pixels
        double rowDst = (CAM_H * PROJ_DST) / p;

        t_vect2 floorL = (t_vect2){(cube->player.x) + rowDst * RayDirL.x, (cube->player.y) + rowDst * RayDirL.y, 0, 0};
        t_vect2 floorR = (t_vect2){(cube->player.x) + rowDst * RayDirR.x, (cube->player.y) + rowDst * RayDirR.y, 0, 0};

        t_vect2 step = (t_vect2){(floorR.x - floorL.x) / SCREEN_WIDTH, (floorR.y - floorL.y) / SCREEN_WIDTH, 0, 0};
        t_vect2 ft_floor = (t_vect2){floorL.x, floorL.y, 0, 0};

        double tmp = 1.0 - (rowDst / MAX_DST);
        if(tmp > 1.0)
            tmp = 1.0;
        else if(tmp < 0.0)
            tmp = 0.0;

        int j = 0;
        while(j < SCREEN_WIDTH)
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
                if(!check_screen_limits(coords))
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

    int i = (SCREEN_HEIGHT / 2);
    while(i < SCREEN_HEIGHT)
    {
        // if replace SCREEN_HEIGHT with SCREEN_WIDTH you get ceiling textures PS: found it by accident :P
        double p = (float)i - SCREEN_HEIGHT / 2.0;
        double rowDst = (CAM_H * PROJ_DST) / p;

        t_vect2 floorL = (t_vect2){(cube->player.x) + rowDst * RayDirL.x, (cube->player.y) + rowDst * RayDirL.y, 0, 0};
        t_vect2 floorR = (t_vect2){(cube->player.x) + rowDst * RayDirR.x, (cube->player.y) + rowDst * RayDirR.y, 0, 0};

        t_vect2 step = (t_vect2){(floorR.x - floorL.x) / SCREEN_WIDTH, (floorR.y - floorL.y) / SCREEN_WIDTH, 0, 0};
        t_vect2 ft_floor = (t_vect2){floorL.x, floorL.y, 0, 0};

        double tmp = 1.0 - (rowDst / MAX_DST);
        if(tmp > 1.0)
            tmp = 1.0;
        else if(tmp < 0.0)
            tmp = 0.0;

        int j = 0;
        while(j < SCREEN_WIDTH)
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
                if(!check_screen_limits(coords))
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
            float scanline = (y % 2 == 0) ? 0.1f : 1.5f;
            int r_x = x - 2;
            int g_x = x;
            int b_x = x + 2;
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
    double PlaneX = -DirY * (HALF_FOV_RAD);
    double PlaneY = DirX * (HALF_FOV_RAD);
    t_vect2 RayDirL = (t_vect2){DirX - PlaneX, DirY - PlaneY,0 ,0};
    t_vect2 RayDirR = (t_vect2){DirX + PlaneX, DirY + PlaneY,0 ,0};
    double mid_point = (SCREEN_HEIGHT / 2.0) + cube->pitch;

    double p = 0;
    mlx_texture_t *tex;
    int i = 0;
    while(i < SCREEN_HEIGHT){
        if(i < mid_point){
            p = (mid_point) - (float)i;
            tex = cube->texture3;
        }
        else{
            p = (float)i - (mid_point);
            tex = cube->texture2;
        }

        if(p == 0.0) p = 1.0;

        double rowDst = (CAM_H * PROJ_DST) / p;

        t_vect2 floorL = (t_vect2){(cube->player.x) + rowDst * RayDirL.x, (cube->player.y) + rowDst * RayDirL.y, 0, 0};
        t_vect2 floorR = (t_vect2){(cube->player.x) + rowDst * RayDirR.x, (cube->player.y) + rowDst * RayDirR.y, 0, 0};

        t_vect2 step = (t_vect2){(floorR.x - floorL.x) / SCREEN_WIDTH, (floorR.y - floorL.y) / SCREEN_WIDTH, 0, 0};
        t_vect2 ft_floor = (t_vect2){floorL.x, floorL.y, 0, 0};

        double tmp = 1.0 - (rowDst / MAX_DST);
        if(tmp > 1.0)
            tmp = 1.0;
        else if(tmp < 0.0)
            tmp = 0.0;

        int j = 0;
        while(j < SCREEN_WIDTH)
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
            int y_iter = SCREEN_WIDTH * i * 4;
            t_vect2 coords = (t_vect2){j, i, 0, 0};
            int iter = 0;
            while(iter < cube->line_girth){
                if(!check_screen_limits(coords)){
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

void ft_upscaling(t_cube *cube){
    uint32_t *prev = (uint32_t *)cube->prev_buffer;
    uint32_t *new = (uint32_t *)cube->image->pixels;
    int y = 0;
    while(y < SCREEN_HEIGHT){
        int x = 0;
        while(x < SCREEN_WIDTH){
            int index = (y * SCREEN_WIDTH) + x;
            int i = 0;
            while(i < UPSCALING_RATE){
                int j = 0;
                while(j < UPSCALING_RATE){
                    new[((y * UPSCALING_RATE + i) * SCREEN_WIDTH_BUFF) + (x * UPSCALING_RATE + j)] = prev[index];
                    j++;
                }
                i++;
            }
            x++;
        }
        y++;
    }
}



void ft_update(void *param)
{
    t_cube *cube;
    struct timeval tv;

    cube = (t_cube *)param;
    // cube->grain = !cube->grain;
    // clear_image(cube);
    // ft_rectangle(cube, (t_vect2){0, 0, 0, 0}, (t_vect2){SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0, 0}, 0x000000ff);
    // ft_rectangle(cube, (t_vect2){0, SCREEN_HEIGHT / 2, 0, 0}, (t_vect2){SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0}, 0x57493eff);
    // draw_grid(cube);
    // draw_player(cub/e);
    gettimeofday(&tv, NULL);
    // ft_ray_init(cube, &cube->player.ray, cube->player.angle);
    ft_draw_rays(cube);
    // ft_ceiling(cube);
    // ft_floor(cube);
    ft_floor_ceiling(cube);
    ft_draw_world(cube);
    // int i = 0;
    // while(i < SCREEN_HEIGHT * SCREEN_WIDTH * 4){
    //     cube->prev_buffer[i] = cube->image->pixels[i];
    //     i++;
    // }
    // i = 0;
    // while(i < SCREEN_HEIGHT * SCREEN_WIDTH * 4){
    //     cube->image->pixels[i] = ft_lerp_pixels(cube->image->pixels[i], cube->prev_buffer[i]);
    //     i++;
    // }
    ft_enemy(cube);
    ft_upscaling(cube);
    cube->final_t = tv.tv_sec;
    ft_mouvement(cube);
    cube->fps++;
    if(cube->final_t - cube->init_t == 1)
    {
        printf("fps : %d, pitch : (%lf)\n", cube->fps, cube->pitch);
        cube->init_t = cube->final_t;
        cube->fps = 0;
    }
    cube->player.pos.x = cube->player.x;
    cube->player.pos.y = cube->player.y;
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
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void ft_map_init(t_cube *cube)
{
    cube->map = ft_calloc(MAP_Y + 1, sizeof(char *));
    if (cube->map == NULL)
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
void ft_init(t_cube *cube)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    cube->prev_buffer = ft_calloc(SCREEN_HEIGHT * SCREEN_WIDTH, 4);
    cube->mod_rate = (FOV * RADIANT_RATE) / RES;
    cube->fps = 0;
    cube->grain = true;
    cube->pitch = 0.0;
    cube->rays = ft_calloc(RES + 1, sizeof(t_ray));
    cube->init_t = tv.tv_sec;
    cube->final_t = tv.tv_sec;
    cube->moving = false;
    cube->player.x = (GRID_SIZE * MAP_X) / 2;
    cube->player.y = (GRID_SIZE * MAP_Y) / 2;
    cube->enemy.x = ((GRID_SIZE * MAP_X) / 2) + 3;
    cube->enemy.y = (GRID_SIZE * MAP_Y) / 2;
    cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
    cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
    cube->player.angle = 0;
    cube->texture = mlx_load_png("./backrooms_final.png");
    cube->texture2 = mlx_load_png("./carpet.png");
    cube->texture3 = mlx_load_png("./ceiling_tiles_color.png");
    cube->texture4 = mlx_load_png("./miku.png");
    cube->line_girth = (int)(SCREEN_WIDTH / RES);
    if(cube->line_girth == 0)
        cube->line_girth = 1;
    cube->mlx = mlx_init(SCREEN_WIDTH_BUFF, SCREEN_HEIGHT_BUFF, "cub3d", true);
    if(cube->mlx == NULL)
    {
        perror("mlx init error :");
        exit(EXIT_FAILURE);
    }
    cube->image = mlx_new_image(cube->mlx, SCREEN_WIDTH_BUFF, SCREEN_HEIGHT_BUFF);
    if(cube->image == NULL)
    {
        mlx_terminate(cube->mlx);
        perror("image init error :");
        exit(EXIT_FAILURE);
    }
    mlx_image_to_window(cube->mlx, cube->image, 0, 0);
    mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_DISABLED);
}

int main()
{
    t_cube cube;
    ft_map_init(&cube);
    // ft_parse(&cube);
    ft_init(&cube);
    mlx_loop_hook(cube.mlx, ft_update, &cube);
    mlx_loop(cube.mlx);
    mlx_terminate(cube.mlx);
    return 0;
}