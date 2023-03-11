#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QMouseEvent>
#include "Pieces.h"
#include "Chessboard.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=NULL);

    // public methods

    void displayStart();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);


    void pickUpPiece(Piece* piece);
    void placePiece(Square* squareToPlace);
    void setPickedPiece();
    bool isWhiteTurn();
    // public attributes
    QGraphicsScene* scene;
    // HexBoard* hexBoard; TODO

    Piece* pieceToPlace;
    Board chessboard;
    QPointF startingPosition;

public slots:
    void start();

private:
    bool whiteTurn=true;


};

#endif // GAME_H
