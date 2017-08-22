#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QDebug>
#include <QMediaPlayer>
#include "gameloop.h"
#include "enemy.h"

class Enemy;

class Player : public QGraphicsPixmapItem
{
private:
    int                 x_pos;
    int                 y_pos;
    int                 up;
    int                 down;
    int                 left;
    int                 right;
    int                 **map;
    QMediaPlayer        *bullet_sound;
    QGraphicsPixmapItem **grid;
    Enemy               *enemy;
    int                 score;
public:
    void        keyPressEvent(QKeyEvent *event);
    int         ft_get_x();
    int         ft_get_y();
    void        ft_set_x(int x);
    void        ft_set_y(int y);
    void        ft_spanw();
    void        ft_create_map(int **map);
    void        ft_update_map(int **map);
    int         **ft_player_map();
    int         ft_rotate_left();
    int         ft_rotate_right();
    int         ft_rotate_up();
    int         ft_rotate_down();
    void        ft_set_grid(QGraphicsPixmapItem **grid)
    {
        this->grid = grid;
    }
    QGraphicsPixmapItem **ft_get_grid()
    {
        return (this->grid);
    }
    Player();
    void    ft_set_enemy(Enemy *e)
    {
        this->enemy = e;
    }
    Enemy   *ft_get_enemy()
    {
        return (this->enemy);
    }
    int     ft_get_score()
    {
        return (this->score);
    }
    void    ft_incr_score()
    {
        this->score++;
    }
};


#endif // PLAYER_H
