#ifndef GHOST_H
#define GHOST_H

#include "gameobject.h"

class Ghost : public GameObject {
public:
    enum Color {Red, Yellow, Pink, Green};
    enum Status {Normal, Panic, Running};

    const static int GhostNum = 4;
    Game *game;

    Ghost(int);
    void move();

    friend class Game;
    friend class Pacman;

private:
    QMediaPlayer* ghost_death_music;

    void moveup();
    void movedown();
    void moveleft();
    void moveright();

    void setdir_randomly();
    void go_out_cage();
    void chase_pacman();
    void dodge_pacman();
    void go_to_cage();
    QPair<int, int> (*chase_strategy)(Ghost*);
    bool overlapable(int, int);

    Color color;
    Status status;
    QVector<QPixmap> anim[4];
    QVector<QPixmap> panic_anim;
    QVector<QPixmap> running_anim;
    int anim_index;
    int release_time;
    bool is_released;
    int panic_time;
};

QPair<int, int> strategy1(Ghost*);
QPair<int, int> strategy2(Ghost*);
QPair<int, int> strategy3(Ghost*);
QPair<int, int> strategy4(Ghost*);

#endif // GHOST_H
