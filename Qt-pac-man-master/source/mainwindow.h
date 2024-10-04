#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QMediaPlayer>
#include <QPushButton>
#include <QTextItem>
#include <QTextBrowser>

#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* = nullptr);
    ~MainWindow();

    void initLabels();
    void keyPressEvent(QKeyEvent*) override;

    Game *game;

    int play_game_clicked;

    Ui::MainWindow *ui;
    Ui::MainWindow *menu;

    QLabel *score_title, *score;
    QLabel *win_label, *lose_label;
    QTimer *score_timer;

public slots:
    void update_score();
};
#endif // MAINWINDOW_H
