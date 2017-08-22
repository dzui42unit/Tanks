#ifndef GAME_LOOP_H
#define GAME_LOOP_H
#define MAP_SIZE 13
#define WIDTH 832
#define HEIGHT 832
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsScene>

class   GameLoop
{
private:
    int             **map;
    int             player_score;

public:

    int     **ft_get_map()
    {
        return (this->map);
    }

    void    ft_update_map(int **map)
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

    void    ft_print_map()
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

    void    ft_set_headquarters()
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

    void    ft_add_obstacle()
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

    void    ft_make_map()
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

    void    ft_destroy_map()
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

    GameLoop()
    {

    }

    ~GameLoop()
    {

    }
};

#endif // GAME_LOOP_H

