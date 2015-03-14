#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include "mainwindow.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <random>
#include <chrono>
#include <QTimer>
#include <QPushButton>
#include <iostream>
#include <vector>
/** @class Gameboard
 *
 * This class contanis the properties of our gameboard
 * including player position, drop positions, and board size
 *
 *
 */
class Gameboard : public QWidget
{
    Q_OBJECT

public slots:
    //tell the drops currently on the board to move down.
       void dropDrops();

public:
    explicit Gameboard(QWidget *parent = 0);
    ~Gameboard();

    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *e);
    void closeEvent(QCloseEvent *e);

    //px=previous position, cx=curent position
    void movePlayer(int px, int cx);

    //was the player hit by this drop?
    bool playerHit(int x, int y);

    void setMainWindow(MainWindow* main_window);

private:
    QPixmap* droplet_image;
    int numdrops;
    QWidget* Top;

    QPoint *player_pos;
    QPoint *drop_positions;

    // Board Variables
    QWidget *Board;
    int board_size;
    QLabel** labels;

    //QuitWidget* qwidget;
    MainWindow* mw;


};

#endif // GAMEBOARD_H
