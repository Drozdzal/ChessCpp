#include "Game.h"
#include "Square.h"
#include "Button.h"
#include <QGraphicsTextItem>
#include "Pieces.h"
#include <iostream>
#include <math.h>
#include <QtCore/QException>
#include <QTimer>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include "Timer.h"

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
    this->loader=Loader();
    this->window = new Window();
    connect(window,&Window::multiplayer,this,&Game::multiplayer);
    connect(window,&Window::createServer,this,&Game::createServer);
    connect(window,&Window::joinServer,this,&Game::joinServer);
    connect(window,&Window::singleplayer,this,&Game::singleplayer);
    connect(window,&Window::loading,this,&Game::loading);
    connect(window,&Window::computer,this,&Game::computer);
    connect(window,&Window::settings,this,&Game::settings);
    connect(window,&Window::addingTimeChanged,this,&Game::addingTimeChanged);
    connect(window,&Window::baseTimeChanged,this,&Game::baseTimeChanged);
    connect(window, &Window::close, this, &Game::close);
    connect(window,&Window::nextMove,this,&Game::nextMove);
    connect(window,&Window::previousMove,this,&Game::previousMove);
    connect(window,&Window::showMainMenu,this,&Game::showMainMenu);
    setScene(window->scene);
    window->displayMenu();
}



// SLOTS
void Game::multiplayer()
{
    window->displayMultiplayer();

}

void Game::createServer(){
    Player playerServer=Player("Michal",true);
//    Player player2=Player("Ewa",false);
    server=new MyServer();
    server->startServer();
    qDebug()<<"Creating server";
    chessboard->createBoard();
    chessboard->createPieces();
    window->clearScene();
    window->displayChessboard(chessboard->board);
    window->displayPieces(chessboard->board.at("A1")->piece->allFigures);
    gameMode = new Multiplayer(playerServer);
    connect(gameMode,&GameMode::quitGame,this,&Game::quitGame);
    gameMode->setChessboard(chessboard);
    inPlayingMode=true;
    gameMode->gameStarted();

}
void Game::joinServer()
{
    Player player1=Player("Michal",false);
//    Player player2=Player("Ewa",true);
    chessboard->createBoard();
    chessboard->createPieces();
    window->clearScene();
    window->displayChessboard(chessboard->board);
    window->displayPieces(chessboard->board.at("A1")->piece->allFigures);
    gameMode = new Multiplayer(player1);
    connect(gameMode,&GameMode::quitGame,this,&Game::quitGame);
    gameMode->setChessboard(chessboard);
    inPlayingMode=true;
    gameMode->gameStarted();

}
void Game::singleplayer()
{
    Player player1=Player("Michal",true);
    Player player2=Player("Ewa",false);
    player1.getTimerWidget()->setTimeRules(timeRemaining,timeAdding);
    player2.getTimerWidget()->setTimeRules(timeRemaining,timeAdding);

    chessboard->createBoard();
    chessboard->createPieces();
    window->clearScene();
    window->displayChessboard(chessboard->board);
    window->displayPieces(chessboard->board.at("A1")->piece->allFigures);
    gameMode = new Singleplayer(player1,player2);

    connect(gameMode,&GameMode::quitGame,this,&Game::quitGame);
    gameMode->setChessboard(chessboard);
    qDebug()<<"przed";

    inPlayingMode=true;
    gameMode->gameStarted();
    window->scene->addItem(gameMode->getPlayer1().getTimerWidget());
    gameMode->getPlayer1().getTimerWidget()->getTimer()->stop();
    gameMode->getPlayer1().getTimerWidget()->setPos(750,600);
    gameMode->getPlayer2().getTimerWidget()->getTimer()->stop();
    window->scene->addItem(gameMode->getPlayer2().getTimerWidget());
    qDebug()<<"po";


}
void Game::loading()
{
    window->clearScene();
//    connect(window,&Window::nextMove,this,&Game::nextMove);
//    connect(window,&Window::previousMove,this,&Game::previousMove);

    QString choosenFile=window->loadingWindow();
    loader.readJson(choosenFile);
    chessboard->createBoard();
    loader.firstMoveFromJson(this->chessboard);
    window->displayChessboard(chessboard->board);
    window->displayPieces(Piece::allFigures);
}
void Game::nextMove()
{

    qDebug()<<"Nacisnieto nexta";
    window->deletePieces(Piece::allFigures);
    loader.moveForward(this->chessboard);
    window->displayPieces(Piece::allFigures);


}
void Game::previousMove()
{
    qDebug()<<"Nacisnieto previous";
    window->deletePieces(Piece::allFigures);
    loader.moveBackward(this->chessboard);
    window->displayPieces(Piece::allFigures);

}
void Game::settings()
{
    qDebug() << "Settings";
    window->displaySettings();
//    client->sendMessage();
}
void Game::computer()
{
    Player player1=Player("Michal",true);
    chessboard->createBoard();
    chessboard->createPieces();
    window->clearScene();
    window->displayChessboard(chessboard->board);
    window->displayPieces(chessboard->board.at("A1")->piece->allFigures);
    gameMode=new Computer(player1);
    connect(gameMode,&GameMode::quitGame,this,&Game::quitGame);
    gameMode->setChessboard(chessboard);
    inPlayingMode=true;

}
void Game::close()
{

    qDebug() << "Quit";
}

void Game::quitGame()
{
    qDebug()<<"Received quti signal";
    this->close();
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
    qDebug()<<"Clicked";
    if ((pieceToMove==nullptr) && inPlayingMode){
        qDebug()<<"Proboje podniesc";
        pieceToMove=gameMode->canPickPiece(event->x(),event->y());



    }
    else if ((pieceToMove!=nullptr)&& inPlayingMode)
    {
        qDebug()<<"executingMove";
        if (gameMode->executeMove(pieceToMove,event->x(),event->y()))
        {

            if (gameMode->isPieceToDelete()!=nullptr)
            {
                window->deletePiece(gameMode->isPieceToDelete());
                gameMode->pieceDeleted();
            }
            saver.piecesToJson();
            saver.save();
            gameMode->swichTurn();
            pieceToMove=nullptr;

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

void Game::baseTimeChanged(QAbstractButton *button){
    std::string buttonText=button->text().toStdString();
    int timeChanged = stoi(buttonText.substr(0,2));
    qDebug()<<"Base time changed to";
    qDebug()<<timeChanged;
    this->timeRemaining=timeChanged;
}

void Game::addingTimeChanged(QAbstractButton *button){
    std::string buttonText=button->text().toStdString();
    int timeChanged = stoi(buttonText.substr(0,2));
    qDebug()<<"Adding time changed to";
    qDebug()<<timeChanged;
    this->timeAdding=timeChanged;
}

void Game::showMainMenu(){
    window->displayMenu();
}
