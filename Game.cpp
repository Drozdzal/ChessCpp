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
    pieceToPlace = nullptr;
    whiteTurn = true;
    this->chessboard = Board();
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
    Player player2=Player("Ewa",false);;
    Singleplayer singleplayer =Singleplayer(player1,player2);
    chessboard.createBoard();
    chessboard.createPieces();
    window->clearScene();
    window->displayChessboard(chessboard.board);
    window->displayPieces(chessboard.board.at("A1")->piece->allFigures);
    this->gameStarted=true;
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
    window->deletePiece(chessboard.board.at(secondarySquare)->piece);
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
int Game::getSquareOnRowColumn(int row,int column){
    return (row-1)*8+(column-1);
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
        qDebug()<<"No kliknelimy";
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
                saver.singlePieceChange(pieceToPlace,secondarySquare);

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
                saver.save();
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

