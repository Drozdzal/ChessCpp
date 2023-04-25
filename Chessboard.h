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
    void setBoard(const std::map<std::string, Square *> &newBoard);
    void resetBoard();
    int sizeOfSquare =75;
    int boardColumnOffset = 75;
    int boardRowOffset =75;
    std::map<std::string,Square*> board;
    std::map<std::string, Square *> getBoard();

};


#endif // CHESSBOARD_H
