#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Square.h"
#include "Pieces.h"


class Board
{

public:
    void createPieces();
    void createBoard();
    void setPieceOnSquare(Piece* piece, std::string sqaurePosition);
//private:
    std::map<std::string,Square*> board;
    int sizeOfSquare=75;
    int boardColumnOffset = 75;
    int boardRowOffset =75;


};


#endif // CHESSBOARD_H
