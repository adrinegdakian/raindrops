#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QRadioButton>

class Instructions;
class Gameboard;

/** @class MainWindow
 *
 * connects Gameboard and Instructions to the mainwindow
 * */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:

public:
    //Will set properties of the mainwindow
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *e);

    ~MainWindow();
    //Will allow access to gameboard and instructions windows
    void setGameboard(Gameboard* game_board);
    void setInstructions(Instructions* instruction);

private:
    Gameboard* board;
    Instructions* my_instr;

    QLabel* welcome;

    QPushButton* instr;
    QPushButton* start;

    QWidget* central;

};

#endif // MAINWINDOW_H
