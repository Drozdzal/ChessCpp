#ifndef PIECES_H
#define PIECES_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QVector2D>

class Piece: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Piece(QGraphicsItem * parent=0);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    bool getIsWhite();
    void setIsPicked(bool picked_state);
    bool getIsPicked();
    virtual bool isMovePossible(int destRow,int destColumn);
    int row;
    int column;
    bool isWhite=true;
    bool firstMove=true;
    bool isPicked=false;

private:


};

class Pawn: public Piece{
    Q_OBJECT
public:
    Pawn(bool isWhite);
    virtual bool isMovePossible(int destRow, int destColumn);
};


class Knight: public Piece{
    Q_OBJECT
public:
    Knight(bool isWhite);
    virtual bool isMovePossible(int destRow, int destColumn);
};

class King: public Piece{
    Q_OBJECT
public:
    King(bool isWhite);
    virtual bool isMovePossible(int destRow, int destColumn);
};

class Queen: public Piece{
    Q_OBJECT
public:
    Queen(bool isWhite);
    virtual bool isMovePossible(int destRow, int destColumn);
};

class Rook: public Piece{
    Q_OBJECT
public:
    Rook(bool isWhite);
    virtual bool isMovePossible(int destRow, int destColumn);
};

class Bishop: public Piece{
    Q_OBJECT
public:
    Bishop(bool isWhite);
    virtual bool isMovePossible(int destRow, int destColumn);
};


#endif // PIECES_H
