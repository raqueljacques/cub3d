#include "../../includes/cub3d.h"

void player_start(t_player *player)
{
    player->x = WIN_WIDTH / 2;
    player->y = WIN_HEIGHT / 2;
    player->key_up = false;
    player->key_down = false;
    player->key_left = false;
    player->key_down = false;
}

int pressing_keys(int key, t_player *player)
{
    if(key == W)
        player->key_up = true;
    if(key == S)
        player->key_down = true;
    if(key == A)
        player->key_left = true;
    if(key == D)
        player->key_right = true;
    return (0);
}

int release_keys(int key, t_player *player)
{
    if(key == W)
        player->key_up = false;
    if(key == S)
        player->key_down = false;
    if(key == A)
        player->key_left = false;
    if(key == D)
        player->key_right = false;
    return (0);
}

void move_player(t_player *player)
{
    int position;

    position = 4;    
    if (player->key_up)
        player->y -= position;
    if (player->key_down)
    {
        player->y += position;
    }
    if (player->key_left)
    {
        player->x -= position;
    }
    if (player->key_right)
    {
        player->x += position;
    }
}