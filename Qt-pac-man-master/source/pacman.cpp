#include "game.h"
#define W (GameObject::Width)

Pacman::Pacman() : GameObject(GameObject::Pacman, QPixmap(":/game_objects/pacman/a3.png")) {
    dir = Stop;
    next_dir = Stop;
    anim_index = 2;

    anim[Right].push_back(QPixmap(":/game_objects/pacman/a1.png"));
    anim[Right].push_back(QPixmap(":/game_objects/pacman/a2.png"));
    anim[Right].push_back(QPixmap(":/game_objects/pacman/a3.png"));
    anim[Right].push_back(QPixmap(":/game_objects/pacman/a4.png"));
    anim[Right].push_back(QPixmap(":/game_objects/pacman/a5.png"));
    anim[Right].push_back(QPixmap(":/game_objects/pacman/a6.png"));
    anim[Right].push_back(QPixmap(":/game_objects/pacman/a5.png"));
    anim[Right].push_back(QPixmap(":/game_objects/pacman/a4.png"));
    anim[Right].push_back(QPixmap(":/game_objects/pacman/a3.png"));
    anim[Right].push_back(QPixmap(":/game_objects/pacman/a2.png"));

    anim[Up].push_back(QPixmap(":/game_objects/pacman/a1.png"));
    anim[Up].push_back(QPixmap(":/game_objects/pacman/b2.png"));
    anim[Up].push_back(QPixmap(":/game_objects/pacman/b3.png"));
    anim[Up].push_back(QPixmap(":/game_objects/pacman/b4.png"));
    anim[Up].push_back(QPixmap(":/game_objects/pacman/b5.png"));
    anim[Up].push_back(QPixmap(":/game_objects/pacman/b6.png"));
    anim[Up].push_back(QPixmap(":/game_objects/pacman/b5.png"));
    anim[Up].push_back(QPixmap(":/game_objects/pacman/b4.png"));
    anim[Up].push_back(QPixmap(":/game_objects/pacman/b3.png"));
    anim[Up].push_back(QPixmap(":/game_objects/pacman/b2.png"));

    anim[Left].push_back(QPixmap(":/game_objects/pacman/a1.png"));
    anim[Left].push_back(QPixmap(":/game_objects/pacman/c2.png"));
    anim[Left].push_back(QPixmap(":/game_objects/pacman/c3.png"));
    anim[Left].push_back(QPixmap(":/game_objects/pacman/c4.png"));
    anim[Left].push_back(QPixmap(":/game_objects/pacman/c5.png"));
    anim[Left].push_back(QPixmap(":/game_objects/pacman/c6.png"));
    anim[Left].push_back(QPixmap(":/game_objects/pacman/c5.png"));
    anim[Left].push_back(QPixmap(":/game_objects/pacman/c4.png"));
    anim[Left].push_back(QPixmap(":/game_objects/pacman/c3.png"));
    anim[Left].push_back(QPixmap(":/game_objects/pacman/c2.png"));

    anim[Down].push_back(QPixmap(":/game_objects/pacman/a1.png"));
    anim[Down].push_back(QPixmap(":/game_objects/pacman/d2.png"));
    anim[Down].push_back(QPixmap(":/game_objects/pacman/d3.png"));
    anim[Down].push_back(QPixmap(":/game_objects/pacman/d4.png"));
    anim[Down].push_back(QPixmap(":/game_objects/pacman/d5.png"));
    anim[Down].push_back(QPixmap(":/game_objects/pacman/d6.png"));
    anim[Down].push_back(QPixmap(":/game_objects/pacman/d5.png"));
    anim[Down].push_back(QPixmap(":/game_objects/pacman/d4.png"));
    anim[Down].push_back(QPixmap(":/game_objects/pacman/d3.png"));
    anim[Down].push_back(QPixmap(":/game_objects/pacman/d2.png"));

    ball_music = new QMediaPlayer();
    ball_music->setMedia(QUrl("qrc:/game_objects/sounds/Eatfruit.mp3"));

    death_music = new QMediaPlayer();
    death_music->setMedia(QUrl("qrc:/game_objects/sounds/Death.mp3"));
}

void Pacman::moveup() {
    anim_index++;
    if (anim_index == anim[Up].size())
        anim_index = 0;
    setPixmap(anim[Up][anim_index]);
    setY(static_cast<int>(y()) - 1);
}

void Pacman::moveleft() {
    anim_index++;
    if (anim_index == anim[Left].size())
        anim_index = 0;
    setPixmap(anim[Left][anim_index]);
    setX(static_cast<int>(x()) - 1);
}

void Pacman::movedown() {
    anim_index++;
    if (anim_index == anim[Down].size())
        anim_index = 0;
    setPixmap(anim[Down][anim_index]);
    setY(static_cast<int>(y()) + 1);
}

void Pacman::moveright() {
    anim_index++;
    if (anim_index == anim[Right].size())
        anim_index = 0;
    setPixmap(anim[Right][anim_index]);
    setX(static_cast<int>(x()) + 1);
}

void Pacman::eat_ball(int y, int x) {
    GameObject *obj = game->map[y][x];
    switch (obj->get_type()) {
        case Ball:
            game->score += obj->get_score();
            game->ball_num--;
            ball_music->play();
            break;
        case PowerBall:
            game->score += obj->get_score();
            game->ball_num--;
            for (int i = 0; i < game->powerball.size(); i++) {
                if (game->powerball.at(i) == obj) {
                    game->powerball.remove(i);
                    break;
                }
            }
            for (int i = 0; i < Ghost::GhostNum; i++) {
                if (game->ghost[i]->status != Ghost::Running) {
                    game->ghost[i]->status = Ghost::Panic;

                    game->ghost[i]->panic_time = PANNIC_TIME;
                    game->ghost_timer[i]->setInterval(PANNIC_INTERVAL);
                }
            }
            break;
        default:
            return;
    }
    QPixmap blankpix;
    game->map[_y][_x] = new GameObject(GameObject::Blank, blankpix);
    game->map[y][x] = this;
    delete obj;
}

bool Pacman::overlapable(int i, int j) {
    if (i < 0 || i >= game->map_height || j < 0 || j >= game->map_width)
        return false;
    switch (game->map[i][j]->get_type()) {
        case Wall:
        case Gate:
            return false;
        default:
            return true;
    }
}

void Pacman::move() {
    int pac_x = static_cast<int>(x());
    int pac_y = static_cast<int>(y());
    int __x = (pac_x - game->geo_x) / W;
    int __y = (pac_y - game->geo_y) / W;
    int x_remainder = (pac_x - game->geo_x) % W;
    int y_remainder = (pac_y - game->geo_y) % W;
    Dir next_dir = get_next_dir();

    if (x_remainder == 0) {
        if (y_remainder == 0) {
            eat_ball(__y, __x);
            _x = __x;
            _y = __y;
            if (game->ball_num == 0) {
                game->stat = Game::Win;
                return;
            }
        }
        switch (next_dir) {
            case Stop:
                dir = next_dir;
                break;
            case Up:
                if (overlapable(_y - 1, _x))
                    dir = next_dir;
                break;
            case Down:
                if (overlapable(_y + 1, _x))
                    dir = next_dir;
                break;
            case Left:
                if (y_remainder == 0 && overlapable(_y, _x - 1))
                    dir = next_dir;
                break;
            case Right:
                if (y_remainder == 0 && overlapable(_y, _x + 1))
                    dir = next_dir;
                break;
        }
    }
    else if (y_remainder == 0) {
        switch (next_dir) {
            case Stop:
                dir = next_dir;
                break;
            case Left:
                if (overlapable(_y, _x - 1))
                    dir = next_dir;
                break;
            case Right:
                if (overlapable(_y, _x + 1))
                    dir = next_dir;
                break;
            default:
                break;
        }
    }

    switch (dir) {
        case Stop:
            break;
        case Up:
            if (y_remainder == 0 && !overlapable(_y - 1, _x)) {
                dir = Stop;
                next_dir = Stop;
            }
            else {
                moveup();
            }
            break;
        case Down:
            if (y_remainder == 0 && !overlapable(_y + 1, _x)) {
                dir = Stop;
                next_dir = Stop;
            }
            else {
                movedown();
            }
            break;
        case Left:
            if (x_remainder == 0 && !overlapable(_y, _x - 1)) {
                dir = Stop;
                next_dir = Stop;
            }
            else
                moveleft();
            break;
        case Right:
            if (x_remainder == 0 && !overlapable(_y, _x + 1)) {
                dir = Stop;
                next_dir = Stop;
            }
            else
                moveright();
            break;
    }
}
