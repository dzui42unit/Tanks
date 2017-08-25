#ifndef GAME_LOOP_H
#define GAME_LOOP_H
#define MAP_SIZE 13
#define WIDTH 1132
#define HEIGHT 832
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "score.h"
#include <QBrush>
#include <QTimer>
#include <QColor>

class Player;
class Enemy;
class Bullet;
class Score;

class   GameLoop : public QGraphicsView
{
private:
    int                 **map;
    QGraphicsScene      *scene;
    QGraphicsView       *viewer;
    QGraphicsPixmapItem **grid;
    Score               *score;
    Player              *player;
    Enemy               *enemy;
    QTimer              *timer_move;
    QTimer              *timer_shoot;
public:
    int     **ft_get_map();
    void    ft_update_map(int **map);
    void    ft_print_map();
    void    ft_set_headquarters();
    void    ft_add_obstacle();
    void    ft_make_map();
    void    ft_destroy_map();
    GameLoop();
    ~GameLoop();
};

#endif // GAME_LOOP_H

