#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gameboard.h"
#include "instructions.h"

/** Initializes parent window
 *
 * Sets text and button properties for main window.
 * @return none
 * */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    // Labels for welcome and categories
    welcome = new QLabel("Welcome to RainDrops!");

    // PushButtons for the categories
    instr = new QPushButton("Intructions");
    start = new QPushButton("Begin");

    // Layout to make the modes line up
    QVBoxLayout* mybuttons = new QVBoxLayout;
    mybuttons->addWidget(welcome);
    mybuttons->addWidget(instr);
    mybuttons->addWidget(start);

   // final_layout->addLayout(two_cols);

    central = new QWidget;
    central->setLayout(mybuttons);

    this->setCentralWidget(central);
    this->setWindowTitle("RainDrops!");


}

/** MainWindow destructor */
MainWindow::~MainWindow() { }

/** To close MainWindow */
void MainWindow::closeEvent(QCloseEvent *e) { }

/** Connect "START" button with click signal
 *
 * @param game_board to open to play on
 * @return none
 * */
void MainWindow::setGameboard(Gameboard* game_board) {
    board = game_board;

    QObject::connect(start, SIGNAL(clicked()), board, SLOT(show()));
}

/** Connect "INSTRUCTIONS" button with click signal
 *
 * @param instruction will be the set of instructions
 * @return none
*/
void MainWindow::setInstructions(Instructions* instruction) {
    my_instr=instruction;
    QObject::connect(instr, SIGNAL(clicked()), my_instr, SLOT(show()));

}




