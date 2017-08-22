#include "gameloop.h"
#include "player.h"

// constructor of a game loop

GameLoop::GameLoop()
{
    ft_make_map();

    // create a a graphic scene and view

    this->scene = new QGraphicsScene();
    this->view = new QGraphicsView();

    // unable scroll

    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // set the scene and view

    this->view->setScene(this->scene);
    this->view->setFixedSize(832, 832);
    this->scene->setSceneRect(0, 0, 832, 832);


    ft_make_grid();

    Player *pl;
    pl = new Player(this->map);
    pl->setPixmap(QPixmap(":/pics/player.png"));
    pl->setFlag(QGraphicsItem::ItemIsFocusable);
    pl->setPos(pl->ft_get_x() * 64, pl->ft_get_y() * 64);
    pl->setFocus();

    this->scene->addItem(pl);

    // start the music

//    QMediaPlayer *media = new QMediaPlayer();
//    media->setMedia(QUrl("qrc:/sound/3 - Track 3.mp3"));
//    media->play();

    this->view->show();
}

void    GameLoop::ft_make_grid()
{
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
            if (this->map[i][j] == 0)
                this->grid[i][j].setPixmap(QPixmap(":/pics/colorstone.png"));
            this->grid[i][j].setPos(j * 64, i * 64);
            this->scene->addItem(&(this->grid[i][j]));
            j++;
        }
        i++;
    }
}

// destructor of the game loop;

GameLoop::~GameLoop()
{
    ft_destroy_map();
}

// member function that adds obstacles to the game map

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

// member function that allocates the map and sets it

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

// adds a headquarter to the game map

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

// deallocates the game map

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
