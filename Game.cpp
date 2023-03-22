#include "Game.h"
#include "Square.h"
#include "Button.h"
#include <QGraphicsTextItem>
#include "Pieces.h"
#include <iostream>
#include <math.h>


Game::Game(QWidget *parent){
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200,900);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1200,900);
    setScene(scene);

    pieceToPlace = nullptr;
    whiteTurn = true;
    this->chessboard = Board();
}

void Game::start(){

    chessboard.startBoard();
    gameStarted=true;


}

void Game::movePiece()
{
    pieceToPlace->setX(chessboard.board.at(secondarySquare)->getX());
    pieceToPlace->setY(chessboard.board.at(secondarySquare)->getY());
    pieceToPlace->actualPosition=secondarySquare;
    chessboard.board.at(primarySquare)->piece=nullptr;
    chessboard.board.at(primarySquare)->setOccupied(false);
    chessboard.board.at(secondarySquare)->piece = pieceToPlace;
    chessboard.board.at(secondarySquare)->setOccupied(true);
    std::cout << "moved" << "\n";

}

void Game::attackPiece()
{
    pieceToPlace->setX(chessboard.board.at(secondarySquare)->getX());
    pieceToPlace->setY(chessboard.board.at(secondarySquare)->getY());
    pieceToPlace->actualPosition=secondarySquare;
    chessboard.board.at(secondarySquare)->piece->actualPosition="00";
    scene->removeItem(chessboard.board.at(secondarySquare)->piece);
    std::cout << "removed item" << "\n";
    chessboard.board.at(primarySquare)->piece=nullptr;
    chessboard.board.at(primarySquare)->setOccupied(false);
    chessboard.board.at(secondarySquare)->piece = pieceToPlace;
    chessboard.board.at(secondarySquare)->setOccupied(true);
}

void Game::backToPrimaryPosition()
{
    pieceToPlace->setX(chessboard.board.at(primarySquare)->getX());
    pieceToPlace->setY(chessboard.board.at(primarySquare)->getY());
    pieceToPlace = nullptr;
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


}


int Game::getSquareOnRowColumn(int row,int column){
    return (row-1)*8+(column-1);
}


bool Game::piecesOnPath(Square *choosenSquare){


    return false;
}
void Game::placePiece(Square *choosenSquare){



}


bool Game::isWhiteTurn()
{
    return Game::whiteTurn;
}


void Game::mouseMoveEvent(QMouseEvent *event){
    if (pieceToPlace!=nullptr)
    {
        pieceToPlace->setPos(event->pos());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){
    // make right click return cardToPlace to originalPos
    if (gameStarted){
    if ((event->button() == Qt::LeftButton) && (pieceToPlace==nullptr))
    {

        primarySquare[0]=getColumnFromPixels(event->x());
        primarySquare[1]=getRowFromPixels(event->y());
        if (chessboard.board.at(primarySquare)->piece !=nullptr &&
               chessboard.board.at(primarySquare)->piece->getIsWhite() == isWhiteTurn() )
        {
        pieceToPlace=chessboard.board.at(primarySquare)->piece;
        }
    }
    else if( (pieceToPlace!=nullptr))
    {
            std::cout<<"checked square"<<pieceToPlace->isSquareOccupied("A2")<<'\n';
            secondarySquare[0]=getColumnFromPixels(event->x());
            secondarySquare[1]=getRowFromPixels(event->y());
            pieceToPlace->getPossibleMoves();
            if (pieceToPlace->movePossible(secondarySquare))
            {
                pieceToPlace->changeFirstMove();
                if (chessboard.board.at(secondarySquare)->isOccupied()){
                    if(pieceToPlace->getIsWhite()!=chessboard.board.at(secondarySquare)->piece->getIsWhite())
                    {
                    attackPiece();
                    changeTurn();
                    }
                }
                else {
                    movePiece();
                    changeTurn();
                }
                pieceToPlace=nullptr;
            }
            else{
            backToPrimaryPosition();
            }


    }




    if (event->button() == Qt::RightButton){
        if (pieceToPlace){
            backToPrimaryPosition();
        }
    }
    }


    QGraphicsView::mousePressEvent(event);
}

void Game::changeTurn(){
    this->whiteTurn= !(this->whiteTurn);
}


char Game::getRowFromPixels(int X)
{
    int row= 1+(X-chessboard.boardRowOffset)/chessboard.sizeOfSquare;
    return (row+'0');
}

char Game::getColumnFromPixels(int Y)
{
    int asciAdd=(Y-chessboard.boardColumnOffset)/chessboard.sizeOfSquare;
    return ((char)(65+asciAdd));
}

