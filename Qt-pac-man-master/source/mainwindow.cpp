#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), menu(new Ui::MainWindow) {
    \
    menu->setupUi(this);
    setWindowTitle(tr("pac-man"));

    QPushButton *welcome = new QPushButton("Welcome to pac-man", this);
    welcome->setStyleSheet("QPushButton {background-color : black; font-family: Fixedsys; color: blue; font-size: 37px;}");
    welcome->setGeometry(QRect(QPoint(140, 100), QSize(400, 50)));

    QMediaPlayer* music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/game_objects/sounds/Beginning.mp3"));
    music->setVolume(100);
    music->play();

    play_game_clicked = 0;

    QPushButton *play_game = new QPushButton("play game", this);
    play_game->setStyleSheet("QPushButton {background-color : yellow ;font-family: Fixedsys; color: black ;font-size: 25px;}");
    play_game->setGeometry(QRect(QPoint(240, 200), QSize(200, 50)));

    QPushButton *exit = new QPushButton("exit", this);
    exit->setStyleSheet("QPushButton {background-color : yellow ;font-family: Fixedsys; color: black ;font-size: 25px;}");
    exit->setGeometry(QRect(QPoint(240, 260), QSize(200, 50)));

    connect(play_game, &QPushButton::clicked, this, [&]() {
        play_game_clicked = 1;

        ui->setupUi(this);
        setWindowTitle(tr("pac-man"));

        ui->graphicsView->setStyleSheet("QGraphicsView {border: none;}");
        ui->graphicsView->setBackgroundBrush(Qt::black);
        ui->graphicsView->setFocusPolicy(Qt::NoFocus);

        int map_height = 20, map_width = 29;
        int x = 50, y = 50;
        int w = (map_width * GameObject::Width);
        int h = (map_height * GameObject::Width);
        ui->graphicsView->setGeometry(x, y, w, h);
        game = new Game(x, y, map_width, map_height, ":/game_objects/map_objects/map.txt");
        ui->graphicsView->setScene(game);
        initLabels();
        game->start();
    });

    connect(exit, &QPushButton::clicked, this, [&]() {
        exit->clearFocus();
    });
}

void MainWindow::initLabels() {
    score_title = new QLabel(this);
    score_title->setText("score");
    score_title->setStyleSheet("QLabel {font-family: Fixedsys; color: white; font-size: 20px;}");
    score_title->setGeometry(50, 12, 60, 26);
    score_title->show();

    score = new QLabel(this);
    score->setIndent(-80);
    score->setText("0");
    score->setStyleSheet("QLabel {font-family: Fixedsys;color: white;font-size: 20px;}");
    score->setGeometry(120, 12, 180, 26);
    score->show();

    win_label = new QLabel(this);
    win_label->hide();
    win_label->setText("You win!");
    win_label->setStyleSheet("QLabel {font-family: Fixedsys;color: yellow;font-size: 25px;}");
    win_label->setGeometry(265, 12, 150, 26);

    lose_label = new QLabel(this);
    lose_label->hide();
    lose_label->setText("You lose!");
    lose_label->setStyleSheet("QLabel {font-family: Fixedsys;color: red;font-size: 25px;}");
    lose_label->setGeometry(265, 12, 150, 26);

    score_timer = new QTimer(this);
    score_timer->start(25);
    connect(score_timer, SIGNAL(timeout()), this , SLOT(update_score()));
}

void MainWindow::update_score() {
    score->setText(QString::number(game->get_score()));
    if (game->stat == Game::Win) {
        win_label->show();
        score_timer->stop();
    }
    if (game->stat == Game::Lose) {
        lose_label->show();
        score_timer->stop();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_W:
        game->pacman_next_direction(GameObject::Up);
        break;
    case Qt::Key_A:
        game->pacman_next_direction(GameObject::Left);
        break;
    case Qt::Key_S:
        game->pacman_next_direction(GameObject::Down);
        break;
    case Qt::Key_D:
        game->pacman_next_direction(GameObject::Right);
        break;
    }
}


MainWindow::~MainWindow() {
    delete ui;
}
