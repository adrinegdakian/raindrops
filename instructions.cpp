#include "instructions.h"
#include "ui_instructions.h"
#include <QLayout>

/** Initialize parent widget.
 * Create a QLabel displaying game instructions.
 * Create a new window to display game instructions which are connected to a pushbutton titled "instructions"
 *
 * @return none
 * */
Instructions::Instructions(QWidget *parent) :
    QWidget(parent)
{
    text=new QWidget();
    QLabel* instr_text = new QLabel("<font size = '8'><font color = 'blue'>Welcome to RainDrops!<br><br> The instructions are simple: Control the green player with the left and right arrow keys. Avoid being hit by the blue water droplets at all costs!<br><br>Good luck!</font>");
    instr_text->setWordWrap(true);
    this->setStyleSheet("background-color:cyan;");
    layout = new QVBoxLayout();
    layout->addWidget(instr_text);
    instr_text->setAlignment(Qt::AlignCenter);
    this->setLayout(layout);

    this->setFixedHeight(400);
    this->setFixedWidth(450);
    this->setWindowTitle("Instructions");
}
/** Destructor for the class*/
Instructions::~Instructions() { }

/** Sets the main window */
void Instructions::setMainWindow(MainWindow* main_window) {
    mw = main_window;
}
