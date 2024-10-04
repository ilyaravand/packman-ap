#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QVector>
#include <QMediaPlayer>

class Game;

class GameObject : public QGraphicsPixmapItem {
public:
    enum ObjectType {Ball, Wall, Gate, Pacman, Ghost, Blank, PowerBall};
    enum Dir {Up = 0, Down = 1, Left = 2, Right = 3, Stop = 4};
    static const int Width = 20;      // game object size by pixel

    GameObject(ObjectType, QPixmap);
    ~GameObject();
    ObjectType get_type();
    int get_x();
    int get_y();
    int get_score();
    void set_score(int);
    void set_dir(Dir);
    void set_next_dir(Dir);
    Dir get_dir();
    Dir get_next_dir();

    friend class Game;
    friend class Ghost;

protected:
    int _x, _y;                 // coordinate in map
    Dir dir;                    // current moving direction
    Dir next_dir;               // next direction by w, a, s, d key
    ObjectType type;
    int score;
};

#endif // GAMEOBJECT_H
