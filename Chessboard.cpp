#include "Chessboard.h"
#include <iostream>
#include "Square.h"


void Board::setPieceOnSquare(Piece* piece, std::string squarePosition){
    Square* square= board.at(squarePosition);
    piece ->setPos(square->getX(),square->getY());
    piece->actualPosition=squarePosition;
    square->setOccupied(true);
    square->piece=piece;
}

std::map<std::string, Square *> Board::getBoard()
{
    return board;
}

void Board::setBoard(const std::map<std::string, Square *> &newBoard)
{
    board = newBoard;
}

int Board::getBoardRowOffset() const
{
    return boardRowOffset;
}

void Board::setBoardRowOffset(int newBoardRowOffset)
{
    boardRowOffset = newBoardRowOffset;
}

int Board::getBoardColumnOffset() const
{
    return boardColumnOffset;
}

void Board::setBoardColumnOffset(int newBoardColumnOffset)
{
    boardColumnOffset = newBoardColumnOffset;
}

int Board::getSizeOfSquare() const
{
    return sizeOfSquare;
}

void Board::setSizeOfSquare(int newSizeOfSquare)
{
    sizeOfSquare = newSizeOfSquare;
}

void Board::createBoard()
{
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
        }
        color=!(color);
    }
}

void Board::createPieces()
{
    std::string squareName = "00";
    for(int i=1;i<=8;i++)
    {
        Pawn* whitePawn = new Pawn(true);
        Pawn* blackPawn = new Pawn(false);
        squareName[0]=char(64+i);
        squareName[1]=7+'0';
        setPieceOnSquare(whitePawn, squareName);
        squareName[1]=2+'0';
        setPieceOnSquare(blackPawn, squareName);
    }
        Rook* whiteRook = new Rook(true);
        setPieceOnSquare(whiteRook, "A8");
        whiteRook = new Rook(true);
        setPieceOnSquare(whiteRook, "H8");

        Rook* blackRook = new Rook(false);
        setPieceOnSquare(blackRook, "A1");
        blackRook = new Rook(false);
        setPieceOnSquare(blackRook, "H1");

        Knight* whiteKnight = new Knight(true);
        setPieceOnSquare(whiteKnight, "B8");
        whiteKnight = new Knight(true);
        setPieceOnSquare(whiteKnight, "G8");

        Knight* blackKnight = new Knight(false);
        setPieceOnSquare(blackKnight, "B1");
        blackKnight = new Knight(false);
        setPieceOnSquare(blackKnight, "G1");


        Bishop* whiteBishop = new Bishop(true);
        setPieceOnSquare(whiteBishop, "C8");
        whiteBishop = new Bishop(true);
        setPieceOnSquare(whiteBishop, "F8");

        Bishop* blackBishop = new Bishop(false);
        setPieceOnSquare(blackBishop, "C1");
        blackBishop = new Bishop(false);
        setPieceOnSquare(blackBishop, "F1");

    King* whiteKing = new King(true);
    setPieceOnSquare(whiteKing, "E8");

    King* blackKing = new King(false);
    setPieceOnSquare(blackKing, "E1");


    Queen* whiteQueen = new Queen(true);
    setPieceOnSquare(whiteQueen, "D8");

    Queen* blackQueen = new Queen(false);
    setPieceOnSquare(blackQueen, "D1");
}

