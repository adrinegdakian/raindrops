#include "gameboard.h"
#include "ui_gameboard.h"

//This sets up a random generator to be used to generate position of droplets
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);

/** Gameboard constructor initializes parent QWidget
 *  Creates a 10x10 grid with 10 drops initially hidden at the top row (gray clouds).
 */
Gameboard::Gameboard(QWidget *parent) : QWidget(parent), board_size(10), numdrops(10)
{
    Top = new QWidget;
    Top->setStyleSheet("QLabel { background-color : black; color : white; }");


    // This layout will space out the elements above
    QHBoxLayout *top_bar = new QHBoxLayout(Top);

    // This code Creates the Board
    Board = new QWidget;
    labels = new QLabel*[board_size*board_size];
    QGridLayout *SquareGrid = new QGridLayout(Board);

    SquareGrid->setGeometry(QRect());
    SquareGrid->setSpacing(0);

    //Random number generator for C++11
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(1,10);


    // Create each label for the board.
    for(int i=0;i<board_size;i++) {
        for(int j=0;j<board_size;j++) {
            // Create label and set properties.
            labels[i*board_size+j] = new QLabel;
            labels[i*board_size+j]->setMinimumSize(40,40);
            labels[i*board_size+j]->setMaximumSize(40,40);
            labels[i*board_size+j]->setStyleSheet("QLabel { background-color : cyan; }");
            labels[i*board_size+j]->setFrameStyle(3);
            labels[i*board_size+j]->setAlignment(Qt::AlignCenter);

            // Add label to the layout
            SquareGrid -> addWidget(labels[i*board_size+j] ,i,j);

        }
    }
    drop_positions=new QPoint[10];
    for (int i=0; i<numdrops; i++){
        drop_positions[i].setX(i);
        drop_positions[i].setY(0);

    }


    // Initialize the muncher at bottom left corner, coordinate (0,9).
    player_pos = new QPoint(0,9);
    int x=player_pos->rx();
    int y=player_pos->ry();
    labels[y*board_size+x]->setStyleSheet("QLabel { background-color: green;}");

    Board->setFixedSize(400,400);

    // Now piece everything together
    //QWidget* CoreWidget = new QWidget;
    // Central Widget composed of Top and Board
    //    Top
    // --------
    //   Board

    // Do not allow board to be resized, otherwise spacings get messed up
      setFixedSize(500,550);

      // Create a vertical box layout for the two pieces
      QVBoxLayout *piece_together = new QVBoxLayout;

      piece_together->addWidget(Top,0,Qt::AlignCenter);
      piece_together->addWidget(Board,0,Qt::AlignCenter);

      this->setLayout(piece_together);
      this->setStyleSheet("QLabel { background-color : white; }");

      // Set the CoreWidget as the central widget to the main window


      QTimer *timer = new QTimer(this);
      connect(timer, SIGNAL(timeout()), this, SLOT(dropDrops()));
      timer->start(20);

      this->setWindowTitle("RainDrops");
}
/** Gameboard destructor to clean up potential memory leaks
 */
Gameboard::~Gameboard()
{
    delete [] player_pos;
    delete [] drop_positions;
}

/** This KeyPressEvent function will move the player left or right
 * based on user input of either left arrow key or right arrow key
 *
 * @param event to be detect which key was pressed
 */
void Gameboard::keyPressEvent(QKeyEvent *event){
    //Get players current positions
    int x = player_pos->rx();
    int y = player_pos->ry();

    //move player based on key pressed
    switch (event->key()) {
    case Qt::Key_Left:
        if(player_pos->rx() != 0)
            movePlayer(x,x-1);

        break;
    case Qt::Key_Right:
        if(player_pos->rx() != board_size-1)
            movePlayer(x,x+1);

        break;
    default:
        QWidget::keyPressEvent(event);
    }
    QCoreApplication::processEvents();
    repaint();
    return;
}

/** this paintEvent function will change the colors of the grid coordinate
 * to blue if a raindrop occupies that coordinate
 * to green if the player occupies that coordinate
 * cyan if nothing occupies that coordinate
 *
 * in that hierarchy
 *
 * @param e unused paintevent parameter
 *  */
void Gameboard::paintEvent(QPaintEvent *e) {

    //obtain players current position
    int x = player_pos->rx();
    int y = player_pos->ry();

    //set player's current position to green
    labels[y*board_size+x]->setStyleSheet("QLabel {background-color: green;}");

    //set drop positions to blue
    for(size_t i=0;i<numdrops;i++) {
        int px = drop_positions[i].rx();
        int py = drop_positions[i].ry();

        if(px >= 0 && py >= 0 && px < board_size && py < board_size)
            labels[py*board_size+px]->setStyleSheet("QLabel {background-color:blue;}");

    }

    //set clouds to grey
    for (int i=0; i<board_size; i++){
        labels[i]->setStyleSheet("QLabel {background-color:grey;}");
    }


}

/** This function moves the position of the player by changing the colors of
 * the grid at the players new position. Players y çoordinate stays constant
 *
 * @param px is the players previous x position
 * @param py is the players current x position
 * */
void Gameboard::movePlayer(int px, int cx){
    labels[90+px]->setStyleSheet("QLabel {background-color:cyan; } ");
    labels[90+cx]->setStyleSheet("QLabel {background-color:green;} ");
    player_pos->setX(cx);
}

/** This function detects if the player overlaps with, or "is hit" by a water droplet"
 * by comparing the relative positions of the two components
 *
 * @param x is the players x position
 * @param y is the players y position
 *
 * @return true is player position overlaps with droplet position
 * @return false if otherwise
 * */
bool Gameboard::playerHit(int x, int y){
    for (int i=0; i<numdrops; i++){
        if (drop_positions[i].rx()==x && drop_positions[i].ry()==y)
            return true;

    }
    return false;
}

/** Water droplets are hidden along each column of the first row, behind a gray "cloud"
 * This function calls for the dropping of a droplet chosen at random by using a random generator
 * of ints between 0 and 9. The x-coordinate corresponding to the random int generated and belonging
 * to the droplet will "fall" and progress downwards by 1 gridspace.
 *
 * @param none
 * @return none
 * */
void Gameboard::dropDrops() {
    std::uniform_int_distribution<int> dripdrop(0,9);

    //select a droplet randomly, store its current positions
    int select=dripdrop(generator);
    int currenty=drop_positions[select].ry();
    int currentx=drop_positions[select].rx();

    //As long as the drop isn't behind the cloud, clean up after it and make its previous position cyan
    if (currenty!=0)
        labels[currenty*board_size+currentx]->setStyleSheet("QLabel {background-color:cyan;}");

    //If the droplet has space to advance, move it down by one element
    if (currenty != 9){
        drop_positions[select].setY(drop_positions[select].ry() + 1);
        labels[ drop_positions[select].ry()*board_size+currentx ]->setStyleSheet("QLabel {background-color:blue;}");
    }
    //If the droplet is on the ground level, check if player hit
    else {
        repaint();
        QCoreApplication::processEvents();

        if (playerHit(currentx, currenty) ) {
            labels[currentx, currenty]->setStyleSheet("QLabel {background-color:red;}");
        }
            labels[ drop_positions[select].ry()*board_size+currentx ]->setStyleSheet("QLabel {background-color:cyan;}");
            drop_positions[select].setY(0);
    }


    repaint();
    QCoreApplication::processEvents();

}
/** This function sets the main window
 *
 * @param main_window
 * @return none
 * */
void Gameboard::setMainWindow(MainWindow* main_window) {
    mw = main_window;

}
/** Closes the main window */
void Gameboard::closeEvent(QCloseEvent *e) {}

