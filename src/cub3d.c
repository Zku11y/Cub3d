/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:13:24 by skully            #+#    #+#             */
/*   Updated: 2025/08/23 15:01:49 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void clear_image(t_cube *cube)
{
    int buffer_size = SCREEN_HEIGHT * SCREEN_WIDTH * 4;
    ft_memset(cube->image->pixels, 0, buffer_size);
}

void ft_angle_limit(double *angle)
{
    if(*angle < 0)
        *angle = (2 * PI) + *angle;
    else if(*angle > (PI * 2))
        *angle = (2 * PI) - *angle;
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
    cube->player.angle += mouse_x * TURN_SPEED;
    mlx_set_mouse_pos(cube->mlx, SCREEN_WIDTH / 2, mouse_y);
}

void ft_mouvement(t_cube *cube)
{
    // if(mlx_is_key_down(cube->mlx, MLX_KEY_D))
    //     cube->player.angle += TURN_SPEED;
    // else if(mlx_is_key_down(cube->mlx, MLX_KEY_A))
    //     cube->player.angle -= TURN_SPEED;
    ft_angle_limit(&cube->player.angle);
    ft_turn(cube);
    if(mlx_is_key_down(cube->mlx, MLX_KEY_D))
    {
        cube->player.x += -1 * sin(cube->player.angle) * PLAYER_SPEED;
        cube->player.y += cos(cube->player.angle) * PLAYER_SPEED;
    }
    else if(mlx_is_key_down(cube->mlx, MLX_KEY_A))
    {
        cube->player.x -= -1 * sin(cube->player.angle) * PLAYER_SPEED;
        cube->player.y -= cos(cube->player.angle) * PLAYER_SPEED;
    }
    if(mlx_is_key_down(cube->mlx, MLX_KEY_W))
    {
        cube->player.x += cos(cube->player.angle) * PLAYER_SPEED;
        cube->player.y += sin(cube->player.angle) * PLAYER_SPEED;
    }
    else if(mlx_is_key_down(cube->mlx, MLX_KEY_S))
    {
        cube->player.x -= cos(cube->player.angle) * PLAYER_SPEED;
        cube->player.y -= sin(cube->player.angle) * PLAYER_SPEED;
    }
    ft_mouvement_limits(cube);
    cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
    cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
}

void ft_draw_line(t_cube *cube, t_vect2 start, t_vect2 finish, int color)
{
    t_vect2 add;
    t_vect2 mod;

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
        if (start.x >= 0 && start.x < SCREEN_WIDTH &&
            start.y >= 0 && start.y < SCREEN_HEIGHT)
        {
            mlx_put_pixel(cube->image, (int)round(start.x), (int)round(start.y), color);
        }
        start.x += add.x;
        start.y += add.y;
    }
}

t_vect2 calc_length(t_cube *cube, t_vect2 hori, t_vect2 vert, t_ray *ray)
{
    double len_hori;
    double len_vert;

    len_hori = (fabs(hori.x - cube->player.x) / cos(ray->angle));
    len_vert = (fabs(vert.y - cube->player.y) / sin(ray->angle));
    if(len_hori < len_vert)
    {
        ray->length = len_hori;
        // ray->length = ray->length * cos(ray->real_angle - cube->player.angle);
        return (hori);
    }
    ray->length = len_vert;
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
    double start_angle;
    int i;

    i = 0;
    start_angle = cube->player.angle - ((FOV / 2) * RADIANT_RATE);
    while(i < RES)
    {
        if(start_angle < 0)
            start_angle = (2 * PI) + start_angle;
        else if(start_angle > (PI * 2))
            start_angle = start_angle - (2 * PI);
        // printf("start angle : %lf\n", start_angle);
        cube->rays[i].real_angle = start_angle;
        ft_ray_init(cube, &(cube->rays[i]), start_angle);
        // ft_draw_line(cube, cube->rays[i].start, cube->rays[i].end, 0xfff700ff);
        i++;
        start_angle += cube->mod_rate;
    }
}

bool check_screen_limits(t_vect2 len)
{
    if(len.x > SCREEN_WIDTH)
        return true;
    else if(len.x < 0)
        return true;
    if(len.y > SCREEN_HEIGHT)
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
    double factor = 1.0 / (1.0 + distance * 0.01); // tweak 0.01
    if(factor < 0.2) factor = 0.2; // keep minimum brightness

    r = (uint8_t)(r * factor);
    g = (uint8_t)(g * factor);
    b = (uint8_t)(b * factor);

    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_draw_world(t_cube *cube)
{
    t_vect2 start;
    t_vect2 end;
    double len;
    int j;
    int i;

    start.x = (SCREEN_WIDTH - (cube->line_girth * RES)) / 2;
    start.y = SCREEN_HEIGHT / 2;
    i = 0;
    while(i < RES)
    {
        j = 0;
        cube->rays[i].length *= cos(cube->rays[i].real_angle - cube->player.angle);
        // len = SCREEN_HEIGHT - cube->rays[i].length;
        // len = (SCREEN_HEIGHT * WALL_SCALE) / cube->rays[i].length;
        // len = 0.5 * GRID_SIZE / tan((FOV / 2) * RADIANT_RATE);
        len = round(SCREEN_HEIGHT * (0.5 * GRID_SIZE / tan((FOV / 2) * RADIANT_RATE)) / cube->rays[i].length);
        start.y = (SCREEN_HEIGHT - len) / 2;
        end.x = start.x;
        end.y = start.y + len;
        while(j < cube->line_girth)
        {
            // if(!check_screen_limits(start) && !check_screen_limits(end))
            set_screen_limits(&start);
            set_screen_limits(&end);
            ft_draw_line(cube, start, end, shade_color(0xff5e00ff, cube->rays[i].length));
            start.x++;
            end.x++;
            j++;
        }
        i++;
    }
}

void ft_update(void *param)
{
    t_cube *cube;
    struct timeval tv;

    cube = (t_cube *)param;
    clear_image(cube);
    // draw_grid(cube);
    ft_mouvement(cube);
    // draw_player(cube);
    cube->fps++;
    gettimeofday(&tv, NULL);
    cube->final_t = tv.tv_sec;
    ft_ray_init(cube, &cube->player.ray, cube->player.angle);
    ft_draw_rays(cube);
    ft_draw_world(cube);
    int32_t mouse_x;    
    int32_t mouse_y;    
    mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
    if(cube->final_t - cube->init_t == 1)
    {
        printf("fps : %d, mouse_pos (%d, %d)\n", cube->fps, mouse_x, mouse_y);
        cube->init_t = cube->final_t;
        cube->fps = 0;
    }
    cube->player.pos.x = cube->player.x;
    cube->player.pos.y = cube->player.y;
    // ft_draw_line(cube, cube->player.pos, cube->player.ray.end, 0x00ff44ff);
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

void ft_map_init(t_cube *cube)
{
    cube->map = ft_calloc(MAP_Y + 1, sizeof(char *));
    if(cube->map == NULL)
    {
        mlx_terminate(cube->mlx);
        perror("Alloc error : ");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while(i < MAP_Y)
    {
        cube->map[i] = ft_calloc(MAP_X + 1, sizeof(char));
        i++;
    }
    i = 0;
    while(i < MAP_X)
    {
        cube->map[0][i] = 1;
        cube->map[i][0] = 1;
        cube->map[MAP_Y - 1][i] = 1;
        cube->map[i][MAP_X - 1] = 1;
        i++;
    }
    cube->map[MAP_Y / 2][MAP_X / 2] = 1;
    cube->map[(MAP_Y / 2) + 1][(MAP_Y / 2) - 1] = 1;
    cube->map[(MAP_Y / 2) + 1][(MAP_Y / 2) + 1] = 1;
}
void ft_init(t_cube *cube)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    cube->mod_rate = (FOV * RADIANT_RATE) / RES;
    cube->fps = 0;
    cube->rays = ft_calloc(RES + 1, sizeof(t_ray));
    cube->init_t = tv.tv_sec;
    cube->final_t = tv.tv_sec;
    cube->moving = false;
    cube->player.x = (GRID_SIZE * MAP_X) / 2;
    cube->player.y = (GRID_SIZE * MAP_Y) / 2;
    cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
    cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
    cube->player.angle = 0;
    cube->line_girth = (int)(SCREEN_WIDTH / RES);
    if(cube->line_girth == 0)
        cube->line_girth = 1;
    cube->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
    if(cube->mlx == NULL)
    {
        perror("mlx init error :");
        exit(EXIT_FAILURE);
    }
    cube->image = mlx_new_image(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
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
