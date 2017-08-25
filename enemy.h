#ifndef ENEMY_H
#define ENEMY_H
#include <ctime>
#include <QTimer>
#include <cstdlib>
#include "player.h"
#include "bullet.h"
#include "gameloop.h"

class   Player;
class   Bullet;
class   GameLoop;

class   Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public slots:
    void    move();
    void    shoot();
private:
    int     **map;
    int     pos_x;
    int     pos_y;
    int     direct;
    Player  *pl;
public:
                Enemy (int **map);
    int         ft_get_x();
    int         ft_get_y();
    void        ft_spawn();
    void        ft_set_pl(Player *pl);
    Player      *ft_get_pl();
    int         ft_get_direct();
};

#endif // ENEMY_H
