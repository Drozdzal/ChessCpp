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
    virtual void getPossibleMoves();
    void changeFirstMove();
    std::string actualPosition="00";
    std::string possiblePosition ="00";
    std::list<std::string> allPossibleMoves;
    bool isSquareOccupied(std::string desiredSquare);
    bool movePossible(std::string desiredSquare);


protected:
    bool isWhite;
    bool firstMove=true;
    static std::list<Piece*> allFigures;




};

class Pawn: public Piece{
    Q_OBJECT
public:
    Pawn(bool isWhite);
    virtual void getPossibleMoves();
};

class Knight: public Piece{
    Q_OBJECT
public:
    Knight(bool isWhite);
    virtual void getPossibleMoves();
};

class King: public Piece{
    Q_OBJECT
public:
    King(bool isWhite);
    virtual void getPossibleMoves();
};

class Queen: public Piece{
    Q_OBJECT
public:
    Queen(bool isWhite);
    virtual void getPossibleMoves();
};

class Rook: public Piece{
    Q_OBJECT
public:
    Rook(bool isWhite);
    virtual void getPossibleMoves();
};

class Bishop: public Piece{
    Q_OBJECT
public:
    Bishop(bool isWhite);
    virtual void getPossibleMoves();
};



#endif // PIECES_H
