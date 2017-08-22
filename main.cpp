#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QTimer>
#include <QColor>
#include <QGraphicsRectItem>
#include <QMediaPlayer>
#include <QGraphicsScene>
#include "player.h"
#include "enemy.h"
#include "gameloop.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QGraphicsScene *scene;
    scene = new QGraphicsScene();

    QGraphicsView *view;
    view = new QGraphicsView();
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene);
    view->setFixedSize(832, 832);
    scene->setSceneRect(0, 0, 832, 832);

    QGraphicsPixmapItem **grid;
    GameLoop            *loop;
    int                 **map;

    loop = new GameLoop();
    loop->ft_make_map();
    map = loop->ft_get_map();

    Player *player;
    player = new Player();
    player->ft_create_map(map);
    player->ft_spanw();
    player->setPixmap(QPixmap(":/pics/player.png"));
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setPos(player->ft_get_x() * 64, player->ft_get_y() * 64);
    player->setFocus();

    int i;
    int j;

    i = 0;
    grid = new QGraphicsPixmapItem *[MAP_SIZE];
    while (i < MAP_SIZE)
    {
        grid[i] = new QGraphicsPixmapItem [MAP_SIZE];
        i++;
    }

    i = 0;
    map = player->ft_player_map();

    Enemy   *enemy = new Enemy(map);
    enemy->setPixmap(QPixmap(":/pics/enemy_d.png"));
    enemy->setPos(enemy->ft_get_x() * 64, enemy->ft_get_y() * 64);
    player->ft_set_enemy(enemy);
    enemy->ft_set_pl(player);
    while (i < MAP_SIZE)
    {
        j = 0;
        while (j < MAP_SIZE)
        {
            if (map[i][j] == 3)
                grid[i][j].setPixmap(QPixmap(":/pics/greystone.png"));
            if (map[i][j] == 5)
                grid[i][j].setPixmap(QPixmap(":/pics/eagle.png"));
            if (map[i][j] == 1)
                grid[i][j].setPixmap(QPixmap(":/pics/greystone.png"));
            if (map[i][j] == 6)
                grid[i][j].setPixmap(QPixmap(":/pics/redbrick.png"));
            if (map[i][j] == 0 || map[i][j] == 9)
                grid[i][j].setPixmap(QPixmap(":/pics/colorstone.png"));
            grid[i][j].setPos(j * 64, i * 64);
            scene->addItem(&(grid[i][j]));
            j++;
        }
        i++;
    }
    scene->addItem(player);
    scene->addItem(enemy);
    player->ft_set_grid(grid);
    grid = player->ft_get_grid();

    QMediaPlayer *media = new QMediaPlayer();
    media->setMedia(QUrl("qrc:/sound/3 - Track 3.mp3"));
    media->play();


    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), enemy, SLOT(move()));
    timer->start(200);

    view->show();

    return a.exec();
}
