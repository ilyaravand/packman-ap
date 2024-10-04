#ifndef PACMAN_H
#define PACMAN_H

#include "gameobject.h"

class Pacman : public GameObject {
public:
    Pacman();
    void move();
    Game *game;

    friend class Game;

private:
    QMediaPlayer* ball_music;
    QMediaPlayer* death_music;

    void moveup();
    void movedown();
    void moveleft();
    void moveright();

    void eat_ball(int, int);
    bool overlapable(int, int);

    QVector<QPixmap> anim[4];
    int anim_index;
};


#endif // PACMAN_H
