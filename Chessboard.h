#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Square.h"
#include "Pieces.h"


class Board
{

  public:
    void startBoard();
    void printSquare();
    void setPieceOnSquare(Piece* piece, Square* sqaure);
//    void resetBoard();
//    void getBoard();

private:
    static QList<Square*> boboard;
    QList<Square*> board;

};


#endif // CHESSBOARD_H
