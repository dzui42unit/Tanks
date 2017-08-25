#include "enemy.h"
#include "gameloop.h"
#include "bullet.h"
#include "player.h"
#include "score.h"
#include <iostream>

class GameLoop;
class Enemy;
class Bullet;
class Player;

void    Enemy::move()
{
    srand(time(0));

    this->direct = rand() % 4 + 1;

    if (this->direct == 4)
    {
        this->setPixmap(QPixmap(":/pics/enemy_l.png"));
        if (this->map[this->pos_y][this->pos_x - 1] == 0)
        {
            this->map[this->pos_y][this->pos_x] = 0;
            this->pos_x--;
            this->setPos(x() - 64, y());
            this->map[this->pos_y][this->pos_x] = 9;
        }
    }
    if (this->direct == 3)
    {
        this->setPixmap(QPixmap(":/pics/enemy_r.png"));
        if (this->map[this->pos_y][this->pos_x + 1] == 0)
        {
            this->map[this->pos_y][this->pos_x] = 0;
            this->setPos(x() + 64, y());
            this->pos_x++;
            this->map[this->pos_y][this->pos_x] = 9;
        }
    }
    if (this->direct == 2)
    {
        this->setPixmap(QPixmap(":/pics/enemy_d.png"));
        if (this->map[this->pos_y + 1][this->pos_x] == 0)
        {
            this->map[this->pos_y][this->pos_x] = 0;
            this->setPos(x(), y() + 64);
            this->pos_y++;
            this->map[this->pos_y][this->pos_x] = 9;
        }
    }
    if (this->direct == 1)
    {
        this->setPixmap(QPixmap(":/pics/enemy.png"));
        if (this->map[this->pos_y - 1][this->pos_x] == 0)
        {
            this->map[this->pos_y][this->pos_x] = 0;
            this->setPos(x(), y() - 64);
            this->pos_y--;
            this->map[this->pos_y][this->pos_x] = 9;
        }
    }
}

Enemy::Enemy (int **map) : QObject(), QGraphicsPixmapItem()
{
    this->direct = 2;
    this->map = map;
    srand(time(0));
    ft_spawn();
}

int         Enemy::ft_get_x()
{
    return (this->pos_x);
}

int         Enemy::ft_get_y()
{
    return (this->pos_y);
}

void        Enemy::ft_spawn()
{
    int choice;

    choice =  rand() % 3 + 1;
    if (choice == 3)
    {
        this->pos_x = 1;
        this->pos_y = 11;
    }
    if (choice == 1)
    {
        this->pos_x = 11;
        this->pos_y = 1;
    }
    if (choice == 2)
    {
        this->pos_x = 11;
        this->pos_y = 11;
    }
}

void        Enemy::ft_set_pl(Player *pl)
{
    this->pl = pl;
}

Player      *Enemy::ft_get_pl()
{
    return (this->pl);
}

void    Enemy::shoot()
{
    Bullet  *bull;

    bull = new Bullet(this->direct, this->map, this->pl, 0);
    if (this->direct == 1 || this->direct == 2)
        bull->setPos(x() + 30, y());
    if (this->direct == 3)
        bull->setPos(x(), y() + 30);
    if (this->direct == 4)
        bull->setPos(x(), y() + 30);
    scene()->addItem(bull);
}

int     Enemy::ft_get_direct()
{
    return (this->direct);
}
