#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QGridLayout>
#include <random>
#include "gameboard.h"
#include "instructions.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Creates main window, gameboard, and instructions
    MainWindow* w = new MainWindow;
    Gameboard* b = new Gameboard;
    Instructions* i = new Instructions;

    //sets properties for above objects
    w->setGameboard(b);
    b->setMainWindow(w);
    w->setInstructions(i);

    //display the window
    w->show();

    return a.exec();
}
