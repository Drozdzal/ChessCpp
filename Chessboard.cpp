#include "Chessboard.h"
#include "Game.h"
#include <iostream>
#include "Square.h"

extern Game * game;

void Board::setPieceOnSquare(Piece* piece, std::string squarePosition){
    Square* square= board.at(squarePosition);
    piece ->setPos(square->getX(),square->getY());
    piece->actualPosition=squarePosition;
    square->setOccupied(true);
    square->piece=piece;
}

void Board::startBoard()
{
    game->scene->clear();
    bool color=false;
    std::string squareName = "00";

    for(int row=0;row<8;row+=1)

    {
        for(int column=0;column<8;column+=1)

        {
            Square* square = new Square();
            square->setPosition(sizeOfSquare*column+boardColumnOffset,sizeOfSquare*row+boardRowOffset);
            square->setColor(color);
            color=!(color);
            squareName[0]=(char)(column+65);
            squareName[1]=(row+1)+'0';
            this->board[squareName]=square;
            game->scene->addItem(square);
        }
        color=!(color);
    }


//    for(int i=1;i<=8;i++)
//    {
//        Pawn* whitePawn = new Pawn(true);
//        Pawn* blackPawn = new Pawn(false);
//        squareName[0]=char(64+i);
//        squareName[1]=7+'0';
//        setPieceOnSquare(whitePawn, squareName);
//        game->scene->addItem(whitePawn);
//        squareName[1]=2+'0';
//        setPieceOnSquare(blackPawn, squareName);
//        game->scene->addItem(blackPawn);
//    }
//        Rook* whiteRook = new Rook(true);
//        setPieceOnSquare(whiteRook, "A8");
//        game->scene->addItem(whiteRook);
//        whiteRook = new Rook(true);
//        setPieceOnSquare(whiteRook, "H8");
//        game->scene->addItem(whiteRook);

//        Rook* blackRook = new Rook(false);
//        setPieceOnSquare(blackRook, "A1");
//        game->scene->addItem(blackRook);
//        blackRook = new Rook(false);
//        setPieceOnSquare(blackRook, "H1");
//        game->scene->addItem(blackRook);

//        Knight* whiteKnight = new Knight(true);
//        setPieceOnSquare(whiteKnight, "B8");
//        game->scene->addItem(whiteKnight);
//        whiteKnight = new Knight(true);
//        setPieceOnSquare(whiteKnight, "G8");
//        game->scene->addItem(whiteKnight);

//        Knight* blackKnight = new Knight(false);
//        setPieceOnSquare(blackKnight, "B1");
//        game->scene->addItem(blackKnight);
//        blackKnight = new Knight(false);
//        setPieceOnSquare(blackKnight, "G1");
//        game->scene->addItem(blackKnight);


//        Bishop* whiteBishop = new Bishop(true);
//        setPieceOnSquare(whiteBishop, "C8");
//        game->scene->addItem(whiteBishop);
//        whiteBishop = new Bishop(true);
//        setPieceOnSquare(whiteBishop, "F8");
//        game->scene->addItem(whiteBishop);

//        Bishop* blackBishop = new Bishop(false);
//        setPieceOnSquare(blackBishop, "C1");
//        game->scene->addItem(blackBishop);
//        blackBishop = new Bishop(false);
//        setPieceOnSquare(blackBishop, "F1");
//        game->scene->addItem(blackBishop);

//    King* whiteKing = new King(true);
//    setPieceOnSquare(whiteKing, "E8");
//    game->scene->addItem(whiteKing);

//    King* blackKing = new King(false);
//    setPieceOnSquare(blackKing, "E1");
//    game->scene->addItem(blackKing);


//    Queen* whiteQueen = new Queen(true);
//    setPieceOnSquare(whiteQueen, "D8");
//    game->scene->addItem(whiteQueen);

//    Queen* blackQueen = new Queen(false);
//    setPieceOnSquare(blackQueen, "D1");
//    game->scene->addItem(blackQueen);
};

//void Board::printSquare()
//{
//    this->board[2]->setColor(Qt::lightGray);
//    game->scene->addItem(this->board[2]);
//}
