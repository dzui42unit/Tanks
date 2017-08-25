#ifndef SCORE_H
#define SCORE_H
#include <QGraphicsItem>
#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
public:
    Score(QGraphicsItem *parent = 0);
    void    ft_increase(int flag);
private:
    int score;
};

#endif // SCORE_H
