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
    pieceToMove = nullptr;
    whiteTurn = true;
    this->chessboard = new Board();
    this->saver=Saver();
    this->window = new Window();
    connect(window,&Window::multiplayer,this,&Game::multiplayer);
    connect(window,&Window::singleplayer,this,&Game::singleplayer);
    connect(window,&Window::loading,this,&Game::loading);
    connect(window,&Window::computer,this,&Game::computer);
    connect(window,&Window::settings,this,&Game::settings);
    connect(window, &Window::close, this, &Game::close);
    setScene(window->scene);
    window->displayMenu();
}



// SLOTS
void Game::multiplayer()
{
    this->server = new MyServer();
    server->startServer();


    this->client= new MyClient();
    client->connectToServer();

}
void Game::singleplayer()
{
    Player player1=Player("Michal",true);
    Player player2=Player("Ewa",false);
    chessboard->createBoard();
    chessboard->createPieces();
    window->clearScene();
    window->displayChessboard(chessboard->board);
    window->displayPieces(chessboard->board.at("A1")->piece->allFigures);
    gameMode = new Singleplayer(player1,player2);
    gameMode->setChessboard(chessboard);
    qDebug()<<"przed";
    inPlayingMode=true;
    gameMode->gameStarted();
    qDebug()<<"po";


}
void Game::loading()
{
    this->client= new MyClient();
    client->connectToServer();
}
void Game::settings()
{
    qDebug() << "Settings";
    client->sendMessage();
}
void Game::computer()
{
    qDebug() << "Computer";
}
void Game::close()
{

    qDebug() << "Quit";
}



void Game::backToPrimaryPosition()
{
    pieceToMove=nullptr;
//    actualizeView();
}
void Game::mouseMoveEvent(QMouseEvent *event){
    if (pieceToMove!=nullptr)
    {
        pieceToMove->setPos(event->pos());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){
    if ((pieceToMove==nullptr) && inPlayingMode){
        qDebug()<<"Proboje podniesc";
        pieceToMove=gameMode->canPickPiece(event->x(),event->y());
    }
    else if ((pieceToMove!=nullptr)&& inPlayingMode)
    {
        if (gameMode->executeMove(pieceToMove,event->x(),event->y()))
        {

            if (gameMode->isPieceToDelete()!=nullptr)
            {
                window->deletePiece(gameMode->isPieceToDelete());
                gameMode->pieceDeleted();
            }
            gameMode->swichTurn();
            pieceToMove=nullptr;
            saver.piecesToJson();
            saver.save();
        }
        else
        {
        Square* previousSquare=chessboard->board.at(pieceToMove->actualPosition);
        pieceToMove->setPos(previousSquare->getX(),previousSquare->getY());
        pieceToMove=nullptr;
        }
    }
    QGraphicsView::mousePressEvent(event);
}

