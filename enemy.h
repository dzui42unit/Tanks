#ifndef ENEMY_H
#define ENEMY_H
#include <ctime>
#include <QTimer>
#include <cstdlib>
#include "player.h"

class   Player;

class   Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public slots:
    void    move()
    {
        srand(time(0));

        int choice;
        choice = rand() % 100 + 1;

        if (choice % 2 == 0)
        {
            this->direct = 4;
            this->setPixmap(QPixmap(":/pics/enemy_l.png"));
            if (this->map[this->pos_y][this->pos_x - 1] == 0)
            {
                this->map[this->pos_y][this->pos_x] = 0;
                this->pos_x--;
                this->setPos(x() - 64, y());
                this->map[this->pos_y][this->pos_x] = 9;
            }
        }
        else if (choice % 3 == 0 || choice % 7 == 0)
        {
            this->direct = 3;
            this->setPixmap(QPixmap(":/pics/enemy_r.png"));
            if (this->map[this->pos_y][this->pos_x + 1] == 0)
            {
                this->map[this->pos_y][this->pos_x] = 0;
                this->setPos(x() + 64, y());
                this->pos_x++;
                this->map[this->pos_y][this->pos_x] = 9;
            }
        }
        else if (choice % 5 == 0 || choice % 10 == 0)
        {
            this->direct = 1;
            this->setPixmap(QPixmap(":/pics/enemy_d.png"));
            if (this->map[this->pos_y + 1][this->pos_x] == 0)
            {
                this->map[this->pos_y][this->pos_x] = 0;
                this->setPos(x(), y() + 64);
                this->pos_y++;
                this->map[this->pos_y][this->pos_x] = 9;
            }
        }
        else
        {
            this->direct = 2;
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
private:
    int     **map;
    int     pos_x;
    int     pos_y;
    int     direct;
    Player  *pl;
public:
    Enemy (int **map) : QObject(), QGraphicsPixmapItem()
    {
        this->direct = 1;
        this->map = map;
        srand(time(0));
        ft_spawn();
    }
    int     ft_get_x()
    {
        return (this->pos_x);
    }
    int     ft_get_y()
    {
        return (this->pos_y);
    }
    void    ft_spawn()
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
    void    ft_set_pl(Player *pl)
    {
        this->pl = pl;
    }
    Player    *ft_get_pl()
    {
        return (this->pl);
    }
};

#endif // ENEMY_H
