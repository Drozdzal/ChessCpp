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

//    void mousePressEvenz t(QGraphicsSceneMouseEvent* event);
    bool getIsWhite();
    bool getFirstMove();
//    virtual bool isMovePossible(int destRow,int destColumn);
    void changeFirstMove();
    std::string actualPosition="00";
    bool isSquareOccupied(std::string desiredSquare);

protected:
    bool isWhite;
    bool firstMove=true;
    static std::list<Piece*> allFigures;




};

class Pawn: public Piece{
    Q_OBJECT
public:
    Pawn(bool isWhite);
//    virtual bool isMovePossible(int destRow, int destColumn);
};

class Knight: public Piece{
    Q_OBJECT
public:
    Knight(bool isWhite);
//    virtual bool isMovePossible(int destRow, int destColumn);
};

class King: public Piece{
    Q_OBJECT
public:
    King(bool isWhite);
//    virtual bool isMovePossible(int destRow, int destColumn);
};

class Queen: public Piece{
    Q_OBJECT
public:
    Queen(bool isWhite);
//    virtual bool isMovePossible(int destRow, int destColumn);
};

class Rook: public Piece{
    Q_OBJECT
public:
    Rook(bool isWhite);
//    virtual bool isMovePossible(int destRow, int destColumn);
};

class Bishop: public Piece{
    Q_OBJECT
public:
    Bishop(bool isWhite);
//    virtual bool isMovePossible(int destRow, int destColumn);
};



#endif // PIECES_H
