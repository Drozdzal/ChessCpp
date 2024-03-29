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
    connect(window,&Window::surrenderButton,this,&Game::clickedSurrender);
    setScene(window->scene);
    window->displayMenu();
}

void Game::clickedSurrender()
{
    qDebug()<<"Opponent clicked surrender";
    QMessageBox msgBox= QMessageBox();
    msgBox.setText("You've surrender");
    msgBox.addButton("Main menu", QMessageBox::AcceptRole);
\
    int result = msgBox.exec();

    switch (result) {
        case QMessageBox::AcceptRole:
            qDebug() << "Know that he lost";
            window->showMainMenu();
            break;
        default:
         break;

}
}

// SLOTS
void Game::multiplayer()
{
    window->displayMultiplayer();


}

void Game::createServer(){
    Player playerServer=Player("Michal",true);
    Player player2=Player("Ewa",false);
    server=new MyServer();
    server->startServer();
    qDebug()<<"Creating server";
    chessboard->createBoard();
    chessboard->createPieces();
    window->clearScene();
    window->displayChessboard(chessboard->board);
    window->displayPieces(chessboard->board.at("A1")->piece->allFigures);
    window->addSurrenderButton(950,300);
    gameMode = new Multiplayer(playerServer,player2);
    connect(gameMode,&GameMode::quitGame,this,&Game::quitGame);
    gameMode->setChessboard(chessboard);
    inPlayingMode=true;
    gameMode->gameStarted();
    gameMode->setMyTurn(true);
    window->scene->addItem(gameMode->getPlayer1().getTimerWidget());
    gameMode->getPlayer1().getTimerWidget()->getTimer()->stop();
    gameMode->getPlayer1().getTimerWidget()->setPos(900,600);
    gameMode->getPlayer2().getTimerWidget()->getTimer()->stop();
    window->scene->addItem(gameMode->getPlayer2().getTimerWidget());
}
void Game::joinServer()
{
    Player player1=Player("Ewa",false);
    Player player2=Player("Michal",true);

    chessboard->createBoard();
    chessboard->createPieces();
    window->clearScene();
    window->displayChessboard(chessboard->board);
    window->displayPieces(chessboard->board.at("A1")->piece->allFigures);
    window->addSurrenderButton(950,300);
    gameMode = new Multiplayer(player1,player2);
    connect(gameMode,&GameMode::quitGame,this,&Game::quitGame);
    gameMode->setChessboard(chessboard);
    inPlayingMode=true;
    gameMode->gameStarted();
    gameMode->opponentMove();

    window->scene->addItem(gameMode->getPlayer1().getTimerWidget());
    gameMode->getPlayer1().getTimerWidget()->getTimer()->stop();
    gameMode->getPlayer2().getTimerWidget()->setPos(900,600);
    gameMode->getPlayer2().getTimerWidget()->getTimer()->stop();
    window->scene->addItem(gameMode->getPlayer2().getTimerWidget());

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
    window->addSurrenderButton(950,300);
    gameMode = new Singleplayer(player1,player2);
    gameMode->setChessboard(chessboard);
    inPlayingMode=true;
    gameMode->gameStarted();
    window->scene->addItem(gameMode->getPlayer1().getTimerWidget());
    gameMode->getPlayer1().getTimerWidget()->getTimer()->stop();
    gameMode->getPlayer1().getTimerWidget()->setPos(900,600);
    gameMode->getPlayer2().getTimerWidget()->getTimer()->stop();
    window->scene->addItem(gameMode->getPlayer2().getTimerWidget());
}
void Game::loading()
{
    window->clearScene();
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
    window->addSurrenderButton(950,300);
    window->scene->addItem(gameMode->getPlayer1().getTimerWidget());
    gameMode->getPlayer1().getTimerWidget()->setPos(900,600);
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
    inPlayingMode=false;
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

    if (inPlayingMode &&(gameMode->isPieceToDelete()!=nullptr))
    {
        window->deletePiece(gameMode->isPieceToDelete());
        gameMode->pieceDeleted();
    }
    QGraphicsView::mouseMoveEvent(event);
}
void Game::mousePressEvent(QMouseEvent *event){
    qDebug()<<"Clicked";
    if((event->x()<675)&&(event->x()>75)){
        if((event->y()<675)&&(event->y()>75)){
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
    inPlayingMode=false;
    window->displayMenu();
    chessboard->resetBoard();

}
