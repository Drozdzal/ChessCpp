#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QMouseEvent>
#include "Pieces.h"
#include "Chessboard.h"
#include "Saver.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=NULL);

    // public methods

    void displayStart();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);


    void placePiece(Square* squareToPlace);
    bool piecesOnPath(Square *choosenSquare);
    void setPickedPiece();
    bool isWhiteTurn();
    void changeTurn();
    void movePiece();
    void attackPiece();
    void backToPrimaryPosition();
    int getSquareOnRowColumn(int row,int column);
    char getColumnFromPixels(int X);
    char getRowFromPixels(int Y);
    // public attributes
    QGraphicsScene* scene;
    Piece* pieceToPlace=nullptr;
    Board chessboard;
    Saver saver;
    std::string primarySquare="00";
    std::string secondarySquare="00";
    bool gameStarted=false;

public slots:
    void start();

private:
    bool whiteTurn=true;


};

#endif // GAME_H
