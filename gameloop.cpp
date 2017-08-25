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
#include "score.h"

int     **GameLoop::ft_get_map()
{
    return (this->map);
}

void    GameLoop::ft_update_map(int **map)
{
    int i;
    int j;

    i = 0;
    while (i < MAP_SIZE)
    {
        j = 0;
        while (j < MAP_SIZE)
        {
            this->map[i][j] = map[i][j];
            j++;
        }
        i++;
    }
}

void    GameLoop::ft_print_map()
{
    int i;
    int j;

    i = 0;
    std::cout << "\t\tGAME MAP\n\n";
    while (i < MAP_SIZE)
    {
        j = 0;
        while (j < MAP_SIZE)
        {
            std::cout << this->map[i][j] << " ";
            j++;
        }
        std::cout << "\n";
        i++;
    }
}

void    GameLoop::ft_set_headquarters()
{
    int i_1;
    int i_2;
    int j_1;
    int j_2;

    j_1 = MAP_SIZE / 2 - 1;
    j_2 = j_1 + 2;
    i_1 = MAP_SIZE - (MAP_SIZE / 4);
    while (j_1 <= j_2)
    {
        this->map[i_1][j_1] = 6;
        j_1++;
    }
    while (i_1 < MAP_SIZE - 1)
    {
        this->map[i_1][j_1 - 1] = 6;
        i_1++;
    }
    i_2 = MAP_SIZE - (MAP_SIZE / 4);
    j_1 = MAP_SIZE / 2 - 1;
    while (i_2 < MAP_SIZE - 1)
    {
        this->map[i_2][j_1] = 6;
        i_2++;
    }
    this->map[MAP_SIZE - 2][MAP_SIZE / 2] = 5;
}

void    GameLoop::ft_add_obstacle()
{
    int i;
    int j;
    int counter;

    srand(time(0));
    counter = 0;
    while (counter < 25)
    {
        i = 2 + rand() % (MAP_SIZE - 1 - 2 + 1);
        j = 2 + rand() % (MAP_SIZE - 1 - 2 + 1);
        if (this->map[i][j] == 0 && i != j)
        {
            this->map[i][j] = 1;
            this->map[i][MAP_SIZE - j - 1] = 1;
            counter++;
        }
    }
}

void    GameLoop::ft_make_map()
{
    int i;
    int j;

    i = 0;
    this->map = new int*[MAP_SIZE];
    while (i < MAP_SIZE)
    {
        this->map[i] = new int[MAP_SIZE];
        i++;
    }
    i = 0;
    while (i < MAP_SIZE)
    {
        j = 0;
        while (j < MAP_SIZE)
        {
            if (i == 0 || i == MAP_SIZE - 1
                    || j == 0 || j == MAP_SIZE - 1)
                this->map[i][j] = 3;
            else
                this->map[i][j] = 0;
            j++;
        }
        i++;
    }
    ft_set_headquarters();
    ft_add_obstacle();
    this->map[1][1] = 0;
    this->map[1][MAP_SIZE - 2] = 0;
    this->map[MAP_SIZE - 2][1] = 0;
    this->map[MAP_SIZE - 2][MAP_SIZE - 2] = 0;
}

void    GameLoop::ft_destroy_map()
{
    int i;

    i = 0;
    while (i < MAP_SIZE)
    {
        delete this->map[i];
        i++;
    }
    delete [](this->map);
}

GameLoop::GameLoop() : QGraphicsView()
{
    this->scene = new QGraphicsScene();
    this->viewer = new QGraphicsView();


    this->viewer->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->viewer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->viewer->setScene(this->scene);
    this->viewer->setFixedSize(1132, 832);
    this->scene->setSceneRect(0, 0, 1132, 832);

    ft_make_map();

    this->score = new Score();

    this->score->setPos(872, 50);

    this->player = new Player();
    this->player->ft_create_map(map);
    this->player->ft_spanw();
    this->player->setPixmap(QPixmap(":/pics/player.png"));
    this->player->setFlag(QGraphicsItem::ItemIsFocusable);
    this->player->setPos(player->ft_get_x() * 64, player->ft_get_y() * 64);
    this->player->setFocus();
    this->scene->setBackgroundBrush(QBrush(QColor(0x009096a0)));

    int i;
    int j;

    i = 0;
    this->grid = new QGraphicsPixmapItem *[MAP_SIZE];
    while (i < MAP_SIZE)
    {
        this->grid[i] = new QGraphicsPixmapItem [MAP_SIZE];
        i++;
    }

    i = 0;
    this->map = player->ft_player_map();

    this->enemy = new Enemy(map);
    this->enemy->setPixmap(QPixmap(":/pics/enemy_d.png"));
    this->enemy->setPos(this->enemy->ft_get_x() * 64, this->enemy->ft_get_y() * 64);
    this->player->ft_set_enemy(this->enemy);
    this->player->ft_set_score(this->score);
    this->enemy->ft_set_pl(this->player);
    while (i < MAP_SIZE)
    {
        j = 0;
        while (j < MAP_SIZE)
        {
            if (this->map[i][j] == 3)
                this->grid[i][j].setPixmap(QPixmap(":/pics/greystone.png"));
            if (this->map[i][j] == 5)
                this->grid[i][j].setPixmap(QPixmap(":/pics/eagle.png"));
            if (this->map[i][j] == 1)
                this->grid[i][j].setPixmap(QPixmap(":/pics/greystone.png"));
            if (this->map[i][j] == 6)
                this->grid[i][j].setPixmap(QPixmap(":/pics/redbrick.png"));
            if (this->map[i][j] == 0 || map[i][j] == 9)
                this->grid[i][j].setPixmap(QPixmap(":/pics/colorstone.png"));
            this->grid[i][j].setPos(j * 64, i * 64);
            this->scene->addItem(&(this->grid[i][j]));
            j++;
        }
        i++;
    }
    this->scene->addItem(this->player);
    this->scene->addItem(this->enemy);
    this->player->ft_set_grid(this->grid);
    this->grid = this->player->ft_get_grid();

    this->timer_move = new QTimer();
    QObject::connect(this->timer_move, SIGNAL(timeout()), this->enemy, SLOT(move()));
    this->timer_move->start(450);
    this->timer_shoot = new QTimer();
    QObject::connect(this->timer_shoot, SIGNAL(timeout()), this->enemy, SLOT(shoot()));
    this->timer_shoot->start(550);

    this->scene->addItem(this->score);

    this->viewer->show();
}

GameLoop::~GameLoop()
{
    int i;

    i = 0;
    while (i < MAP_SIZE)
    {
        delete this->map[i];
        i++;
    }
    delete []this->map;
    i = 0;
    while (i < MAP_SIZE)
    {
        delete this->grid[i];
        i++;
    }
    delete []this->grid;
    delete this->scene;
    delete this->viewer;
    delete this->score;
    delete this->player;
    delete this->enemy;
    delete this->timer_move;
    delete this->timer_shoot;
}
