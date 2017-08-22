#include "enemy.h"

Enemy::Enemy(int **map)
{
    this->up = 0;
    this->down = 1;
    this->left = 0;
    this->right = 0;
    this->map = map;
//    ft_spawn();
}

void    Enemy::ft_spawn()
{
    int i;
    int j;

    i = 1;
    while (i < MAP_SIZE)
    {
        j = MAP_SIZE - 1;
        while (j > 0)
        {
            if (this->map[i][j] == 0)
            {
               this->pos_x = i;
               this->pos_y = j;
                return ;
            }
            j--;
        }
        i++;
    }
}

int     Enemy::ft_get_enemy_x()
{
    return (this->pos_x);
}

int     Enemy::ft_get_enemy_y()
{
    return (this->pos_y);
}
