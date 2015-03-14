#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <QWidget>
#include "mainwindow.h"
#include <QVBoxLayout>

class MainWindow;

/** @class Instruction
 *
 * Will contain a label to display instructions to the user
 * when prompted by click of QPushButton labeled "Instructions"
 * */
class Instructions : public QWidget
{
    Q_OBJECT

public:
    explicit Instructions(QWidget *parent = 0);
    void setMainWindow(MainWindow* main_window);

    ~Instructions();

private:
    QWidget* text;
    QVBoxLayout* layout;

    MainWindow* mw;
};


#endif // INSTRUCTIONS_H
