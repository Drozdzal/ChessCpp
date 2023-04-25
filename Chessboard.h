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
    int sizeOfSquare =75;
    int boardColumnOffset = 75;
    int boardRowOffset =75;
    std::map<std::string,Square*> board;

public:
    std::map<std::string, Square *> getBoard();
    int getSizeOfSquare() const;
    void setSizeOfSquare(int newSizeOfSquare);
    int getBoardColumnOffset() const;
    void setBoardColumnOffset(int newBoardColumnOffset);
    int getBoardRowOffset() const;
    void setBoardRowOffset(int newBoardRowOffset);
};


#endif // CHESSBOARD_H
