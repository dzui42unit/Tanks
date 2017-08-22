#include "player.h"
#include "gameloop.h"
#include "bullet.h"
#include <QGraphicsScene>
#include <QDebug>

Player::Player()
{
    this->up = 0;
    this->down = 1;
    this->left = 0;
    this->right = 0;
    this->score = 0;
    this->bullet_sound = new QMediaPlayer();
    this->bullet_sound->setMedia(QUrl("qrc:/sound/gun-gunshot-01.mp3"));
}

void    Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        this->setPixmap(QPixmap(":/pics/player_l.png"));
        this->left = 1;
        this->right = 0;
        this->up = 0;
        this->down = 0;
        if (this->map[this->x_pos][this->y_pos - 1] == 0)
        {
            this->y_pos--;
            setPos(x() - 64, y());
        }
    }
    if (event->key() == Qt::Key_Right)
    {
        this->setPixmap(QPixmap(":/pics/player_r.png"));
        this->left = 0;
        this->right = 1;
        this->up = 0;
        this->down = 0;
        if (this->map[this->x_pos][this->y_pos + 1] == 0)
        {
            setPos(x() + 64, y());
            this->y_pos++;
        }
    }
    if (event->key() == Qt::Key_Down)
    {
        this->setPixmap(QPixmap(":/pics/player.png"));
        this->left = 0;
        this->right = 0;
        this->up = 0;
        this->down = 1;
        if (this->map[this->x_pos + 1][this->y_pos] == 0)
        {
            setPos(x(), y() + 64);
            this->x_pos++;
        }
    }
    if (event->key() == Qt::Key_Up)
    {
        this->setPixmap(QPixmap(":/pics/player_u.png"));
        this->left = 0;
        this->right = 0;
        this->up = 1;
        this->down = 0;
        if (this->map[this->x_pos - 1][this->y_pos] == 0)
        {
            this->x_pos--;
            setPos(x(), y() - 64);
        }
    }
    if (event->key() == Qt::Key_Space)
    {
        int direct;

        // create a bullet

        if (this->up)
            direct = 1;
        if (this->down)
            direct = 2;
        if (this->right)
            direct = 3;
        if (this->left)
            direct = 4;
        Bullet *bullet;
        bullet = new Bullet(direct, this->map, this);
        if (direct == 1 || direct == 2)
            bullet->setPos(x() + 30, y());
        if (direct == 3)
            bullet->setPos(x(), y() + 30);
        if (direct == 4)
            bullet->setPos(x(), y() + 30);
        scene()->addItem(bullet);

        // play bullet sound

        if (this->bullet_sound->state() == QMediaPlayer::PlayingState)
            this->bullet_sound->setPosition(0);
        if (this->bullet_sound->state() == QMediaPlayer::StoppedState)
            this->bullet_sound->play();
    }
}

void    Player::ft_update_map(int **map)
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

int     Player::ft_get_x()
{
    return (this->x_pos);
}

int     Player::ft_get_y()
{
    return (this->y_pos);
}

void    Player::ft_set_x(int x)
{
    this->x_pos = x;
}

void    Player::ft_set_y(int y)
{
    this->y_pos = y;
}

void    Player::ft_spanw()
{
    int i;
    int j;

    i = 0;
    while (i < MAP_SIZE)
    {
        j = 0;
        while (j < MAP_SIZE)
        {
            if (this->map[i][j] == 0)
            {
                this->x_pos = i;
                this->y_pos = j;
                return ;
            }
            j++;
        }
        i++;
    }
}

void    Player::ft_create_map(int **map)
{
    int i;
    int j;

    this->map = new int *[MAP_SIZE];
    i = 0;
    while (i < MAP_SIZE)
    {
        j = 0;
        this->map[i] = new int [MAP_SIZE];
        while (j < MAP_SIZE)
        {
            this->map[i][j] = map[i][j];
            j++;
        }
        i++;
    }
}

int     **Player::ft_player_map()
{
    return (this->map);
}
