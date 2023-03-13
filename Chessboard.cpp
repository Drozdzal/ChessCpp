#include "Chessboard.h"
#include "Game.h"
#include <iostream>
#include "Square.h"

extern Game * game;
QList<Square*> Board::boboard = QList<Square*>();


void Board::startBoard()
{
    int asci_val=66;
    bool color=false;
    QList<Square*> squares;

    for(int row=1;row<=8;row+=1)
    {
        for(int column=1;column<=8;column+=1)
        {
            Square* square = new Square();
            square->setPosition(75*row,75*column);
            square->setColor(color);
            square->column=column;
            square->row=row;
            asci_val+=1;
            color=!(color);
//            Board::boboard.append(square);
            this->board.append(square);
            game->scene->addItem(square);
        }
        color=!(color);
    }

    Pawn* whitePiece = new Pawn(true);
    whitePiece->setPos(20,40);
    game->scene->addItem(whitePiece);

    Knight* blackPiece = new Knight(true);
    blackPiece->setPos(400,50);
    game->scene->addItem(blackPiece);

    Rook* blackPiece2 = new Rook(true);
    blackPiece2->setPos(200,50);
    game->scene->addItem(blackPiece2);

    Queen* blackPiece3 = new Queen(true);
    blackPiece3->setPos(250,100);
    game->scene->addItem(blackPiece3);
};

void Board::printSquare()
{
    this->board[2]->setColor(Qt::lightGray);
    game->scene->addItem(this->board[2]);
}
