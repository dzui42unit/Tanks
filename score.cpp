#include "score.h"
#include "enemy.h"
#include "player.h"
#include "gameloop.h"
#include "bullet.h"
#include <QFont>

class Enemy;
class GameLoop;
class Bullet;
class Player;

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    // set the score

    this->score = 0;

    // draw text

    setPlainText("SCORE: " + QString::number(this->score) + "\nSPACEBAR TO SHOOT\nARROWS TO MOVE\n");
    setDefaultTextColor(0x00e27d09);
    setFont(QFont("times", 15));
}

void    Score::ft_increase(int flag)
{
    if (flag == 1)
    {
        this->score += 10;
        setPlainText("SCORE: " + QString::number(this->score) + "\nSPACEBAR TO SHOOT\nARROWS TO MOVE\n");
    }
    if (flag == 2)
    {
        if (this->score >= 40)
        {
            setPlainText("YOU WIN");
            setFont(QFont("times", 60));
            setPos(300, 400);
        }
        else
        {
            setPlainText("YOU LOSE");
            setFont(QFont("times", 60));
            setPos(300, 400);
        }
    }
}

