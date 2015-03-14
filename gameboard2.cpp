#include "gameboard.h"
#include "ui_gameboard.h"

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);

GameBoard::GameBoard(QWidget *parent) : QWidget(parent), board_size(10), numdrops(10);
{
    Top = new QWidget;
    Top->setStyleSheet("QLabel { background-color : black; color : white; }");


    // This layout will space out the elements above
    QHBoxLayout *top_bar = new QHBoxLayout(Top);

    // Fix a total of 3 lives for now, can change later.
    // One life is currently playing, the others are listed above
    lives_remaining = 3;
    lives = new QLabel*[lives_remaining-1];
    // This line above is important, it is an array of QLabel POINTERS.
    // You have to input heap memory pointers for the memory management system to work properly.


    // Set the labels to have the muncher image, add to the top bar layout.
    for(size_t i=0;i<lives_remaining-1;i++) {
        lives[i] = new QLabel("Lives: " + QString::number(lives_remaining));
        lives[i]->setMinimumSize(40,40);
        lives[i]->setMaximumSize(40,40);
        lives[i]->setScaledContents(true);
        top_bar->addWidget(lives[i]);
    }

    // This code Creates the Board
    Board = new QWidget;
    labels = new QLabel*[board_size*board_size];
    values = new int[board_size*board_size];
    QGridLayout *SquareGrid = new QGridLayout(Board);

    SquareGrid->setGeometry(QRect());
    SquareGrid->setSpacing(0);

    // Random number generator for C++11
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

    for (int i=0; i<numdrops; i++){
        drop_positions[i].setX(i);
        drop_positions[i].setY(0);

    }


    // Initialize the muncher at top left corner, coordinate (0,9).
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
      timer->start(100);

      this->setWindowTitle("Raindrops");

}

GameBoard::~GameBoard() {
    // According to
    delete [] values;
    delete [] player_pos;

}

void GameBoard::keyPressEvent(QKeyEvent *event){

    int x = player_pos->rx();
    int y = player_pos->ry();

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

void GameBoard::paintEvent(QPaintEvent *e) {

    int x = player_pos->rx();
    int y = player_pos->ry();


    for (int i=0; i<board_size; i++){
        labels[i]->setStyleSheet("QLabel {background-color:white;}");
    }

    //player's current position
    labels[y*board_size+x]->setStyleSheet("QLabel {background-color: green;}");

    for(size_t i=0;i<numdrops;i++) {
        int px = drop_positions[i].rx();
        int py = drop_positions[i].ry();

        if(px >= 0 && py >= 0 && px < board_size && py < board_size)
            labels[py*board_size+px]->setStyleSheet("QLabel {background-color:blue;}");

    }




}

void GameBoard::movePlayer(int px, int cx){
    label[90+px]->setStyleSheet("QLabel {background-color:cyan; } ");
    label[90+cx]->setStyleSheet("QLabel {background-color:green;} ");
    player_pos->setX(cx);
}

bool GameBoard::playerHit(int x, int y){
    for (int i=0; i<numdrops; i++){
        if (drop_positions[i].rx()==x && drop_positions[i].ry()==y)
            return true;

    }
    return false;
}

void GameBoard::dropDrops() {
    std::uniform_int_distribution<int> dripdrop(0,9);

    int select=dripdrop(generator);
    int currenty=drop_positions[select]->ry();
    int currentx=drop_positions[select]->rx();

    if (currenty!=0)
        label[currenty*board_size+currentx]->setStyleSheet("QLabel {background-color:cyan;}");



    if (currenty+1 !=9){
        drop_positions[select]->setY(drop_positions[select]->ry + 1);
        label[drop_positions[select]->ry*board_size+currentx]->setStyleSheet("QLabel {background-color:blue;}");
    }
    else
        drop_positions[select]->setY(0);

    repaint();
    QCoreApplication::processEvents();

}

void GameBoard::closeEvent(QCloseEvent *e) {

    //e->ignore();
    //qwidget.show();

}

void GameBoard::setMainWindow(MainWindow* main_window) {
    mw = main_window;

}

