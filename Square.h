#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include "Pieces.h"

class Square: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Square();
    void setPosition(int x,int y);
    void setColor(bool isWhite);
    bool isOccupied();
    void setOccupied(bool isOccupied);
    int getX();
    int getY();
    void setX(int X);
    void setY(int Y);
    Piece* piece=nullptr;
private:
    int width=75;
    int height=75;
    bool occupied=false;
    bool isWhite;
    int X;
    int Y;
};


#endif // SQUARE_H
