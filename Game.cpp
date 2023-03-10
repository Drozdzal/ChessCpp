#include "Game.h"
#include "Square.h"
#include "Button.h"
#include <QGraphicsTextItem>
#include "Pieces.h"
#include <iostream>


Game::Game(QWidget *parent){
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);

    pieceToPlace = nullptr;
    whiteTurn = true;
    this->chessboard = Board();
}

void Game::start(){
    std::cout << "Jestem w starcie";
    chessboard.startBoard();


}


void Game::displayStart(){
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Chess Game - MZ"));
    QFont titleFont("arial",80);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 100;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the quit button
    Button* multiplayerButton = new Button(QString("Play Multiplayer"));
    int mbxPos = this->width()/2 - multiplayerButton->boundingRect().width()/2;
    int mbyPos = 275;
    multiplayerButton->setPos(mbxPos,mbyPos);
    connect(multiplayerButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(multiplayerButton);


    // create the play button
    Button* singleplayerButton = new Button(QString("Play Singleplayer"));
    int spxPos = this->width()/2 - singleplayerButton->boundingRect().width()/2;
    int spyPos = 350;
    singleplayerButton->setPos(spxPos,spyPos);
    connect(singleplayerButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(singleplayerButton);

    // create the quit button
    Button* computerButton = new Button(QString("Play against computer"));
    int cxPos = this->width()/2 - computerButton->boundingRect().width()/2;
    int cyPos = 425;
    computerButton->setPos(cxPos,cyPos);
    connect(computerButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(computerButton);

    // create the quit button
    Button* settingsButton = new Button(QString("Settings"));
    int sxPos = this->width()/2 - settingsButton->boundingRect().width()/2;
    int syPos = 500;
    settingsButton->setPos(sxPos,syPos);
    connect(settingsButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(settingsButton);

    // create the quit button
    Button* loadButton = new Button(QString("Load Game"));
    int lxPos = this->width()/2 - loadButton->boundingRect().width()/2;
    int lyPos = 575;
    loadButton->setPos(lxPos,lyPos);
    connect(loadButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(loadButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 650;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
    std::cout << "Jestem w starcie";

}


void Game::pickUpPiece(Piece* piece){
    // picks up the specified card
    if (piece->getIsWhite() == isWhiteTurn() && pieceToPlace == NULL){
        pieceToPlace = piece;
        startingPosition = piece->pos();
        return;
}


}


void Game::placePiece(Square *choosenSquare){
        if (pieceToPlace->isMovePossible(choosenSquare->row,choosenSquare->column)){
            pieceToPlace ->setPos(choosenSquare->xp,choosenSquare->yp);
            pieceToPlace->row=choosenSquare->row;
            pieceToPlace->column=choosenSquare->column;
            std::cout  << pieceToPlace->row << '\n';
            std::cout  << pieceToPlace->column << '\n';
            pieceToPlace = nullptr;
        }
        else
        {
            std::cout << "Move is not possible";
        }


}


bool Game::isWhiteTurn()
{
    return Game::whiteTurn;
}


void Game::mouseMoveEvent(QMouseEvent *event){
    // if there is a cardToPlace, then make it follow the mouse
    if (pieceToPlace!=nullptr){
        pieceToPlace->setPos(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){
    // make right click return cardToPlace to originalPos
    if (event->button() == Qt::RightButton){
        if (pieceToPlace){
            pieceToPlace->setPos(startingPosition);
            pieceToPlace = NULL;
        }
    }
//    else if (event->button() == Qt::LeftButton){
//        if (pieceToPlace){
//            pieceToPlace->setPos(event->pos());
//            pieceToPlace = NULL;
//        }
//    }

    QGraphicsView::mousePressEvent(event);
}



