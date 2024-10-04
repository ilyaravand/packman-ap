#include "mainwindow.h"
#include <QApplication>
#include <QTime>

void delay() {
    QTime dieTime = QTime::currentTime().addSecs(5);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    while (true) {
        MainWindow w;
        w.show();
        while (w.play_game_clicked == 0 || (w.game->stat != Game::Lose && w.game->stat != Game::Win))
            delay();
    }
    return a.exec();
}
