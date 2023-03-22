#include "Square.h"
#include <QBrush>
#include "Game.h"
#include <iostream>
extern Game * game;

Square::Square(){
    // drew the rect



}
void Square::setPosition(int x,int y){
    this->X=x;
    this->Y=y;
    setRect(X,Y,width=width,height=height);
}

void Square::setColor(bool isWhite)
{
    Square::isWhite=isWhite;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    if (isWhite){
        brush.setColor(Qt::white);
    }
    else{
        brush.setColor(Qt::darkGray);
    }

    setBrush(brush);
}


bool Square::isOccupied(){
    return this->occupied;
}

void Square::setOccupied(bool isOccupied){
    this->occupied=isOccupied;
}

int Square::getX()
{
    return this->X;
}

int Square::getY()
{
    return this->Y;
}

void Square::setX(int X)
{
    this->X=X;
}

void Square::setY(int Y)
{
    this->Y=Y;
}
