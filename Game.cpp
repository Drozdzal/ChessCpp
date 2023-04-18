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
    connect(window, &Window::close, this, &Game::close);
    connect(window,&Window::nextMove,this,&Game::nextMove);
    connect(window,&Window::previousMove,this,&Game::previousMove);
    setScene(window->scene);




//       QLabel* label= new QLabel();
//       label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//       label->setFixedSize(150, 50);
//           QGraphicsProxyWidget* proxy = window->scene->addWidget(label);
////           proxy->setPos(, 100);

//       QTimer timer;
//       timer.setInterval(1000);
//       int remaining_time = 10 * 60;
//       label->setText(QString("%1:%2").arg(remaining_time / 60, 2, 10, QLatin1Char('0')).arg(remaining_time % 60, 2, 10, QLatin1Char('0')));
//       QObject::connect(&timer, &QTimer::timeout, [&](){
//           remaining_time--;
//           if (remaining_time < 0) {
//               remaining_time = 0;
//               timer.stop();
//           }
//           label->setText(QString("%1:%2").arg(remaining_time / 60, 2, 10, QLatin1Char('0')).arg(remaining_time % 60, 2, 10, QLatin1Char('0')));
//       });
////       window->scene->addWidget(label);
//       timer.start();






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
    chessboard->createBoard();
    chessboard->createPieces();
    window->clearScene();
    window->displayChessboard(chessboard->board);
    window->displayPieces(chessboard->board.at("A1")->piece->allFigures);
    gameMode = new Singleplayer(player1,player2);
    connect(gameMode,&GameMode::quitGame,this,&Game::quitGame);
    gameMode->setChessboard(chessboard);
    qDebug()<<"przed";


    TimerWidget* timer=new TimerWidget();
    window->scene->addItem(timer);
    inPlayingMode=true;
    gameMode->gameStarted();
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
//        gameMode->isMate(pieceToMove);
//        gameMode->isFinished(pieceToMove);


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

