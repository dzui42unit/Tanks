#include "bullet.h"
#include <QTimer>
#include "player.h"
#include "gameloop.h"
#include <QGraphicsScene>
#include <iostream>

Bullet::Bullet(int direct, int **map, Player *pl) : QObject() , QGraphicsPixmapItem()
{
    // draw a bullet

    this->map = map;
    this->direct = direct;
    this->enemy = pl->ft_get_enemy();
    if (this->direct == 1)
        setPixmap(QPixmap(":/pics/shot.png"));
    if (this->direct == 2)
        setPixmap(QPixmap(":/pics/shot_d.png"));
    if (this->direct == 3)
        setPixmap(QPixmap(":/pics/shot_r.png"));
    if (this->direct == 4)
        setPixmap(QPixmap(":/pics/shot_l.png"));
    this->timer = new QTimer();
    this->pl = pl;
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(5);
}

void    Bullet::move()
{
    float   x_p;
    float   y_p;
    int     check_x;
    int     check_y;

    if (this->direct == 1)
    {
        x_p = x();
        y_p = y() - 5;
    }
    if (this->direct == 2)
    {
        x_p = x();
        y_p = y() + 5;
    }
    if (this->direct == 3)
    {
        x_p = x() + 5;
        y_p = y();
    }
    if (this->direct == 4)
    {
        x_p = x() - 5;
        y_p = y();
    }
    check_x = int(x_p / 64);
    check_y = int(y_p / 64);
    setPos(x_p, y_p);

    if (this->map[check_y][check_x])
    {
        if (this->map[check_y][check_x] != 3 && this->map[check_y][check_x] != 9)
        {
            this->map[check_y][check_x] = 0;
            this->pl->ft_update_map(this->map);
            QGraphicsPixmapItem **grid;
            grid = this->pl->ft_get_grid();
            grid[check_y][check_x].setPixmap(QPixmap(":/pics/colorstone.png"));
        }
        if (this->map[check_y][check_x] == 9)
        {
            this->pl->ft_incr_score();
            this->map[check_y][check_x] = 0;
            this->enemy->ft_spawn();
            this->enemy->setPos(this->enemy->ft_get_x() * 64, this->enemy->ft_get_y() * 64);
            this->map[this->enemy->ft_get_y()][this->enemy->ft_get_x()] = 9;
            this->pl->ft_update_map(this->map);
        }
        scene()->removeItem(this);
        delete this->timer;
        delete this;
    }
}
