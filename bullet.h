#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include "player.h"
#include "enemy.h"

class Player;
class Enemy;

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QTimer              *timer;
    int                 direct;
    int                 **map;
    Player              *pl;
    Enemy               *enemy;
public:
    Bullet(int direct, int **map, Player *pl);
    int     **ft_get_map();
    int     ft_check_hit(int x, int y);
public slots:
    void    move();
};

#endif // BULLET_H
