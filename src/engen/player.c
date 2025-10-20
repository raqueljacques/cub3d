#include "../../includes/cub3d.h"

void player_start(t_player *player, t_game *game)
{
    game->player_x = WIN_WIDTH / 2;
    game->player_y = WIN_HEIGHT / 2;
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