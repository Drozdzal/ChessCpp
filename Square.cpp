#include "Square.h"
#include <QBrush>
#include "Game.h"
#include <iostream>
extern Game * game;

Square::Square(){
    // drew the rect



}
void Square::setPosition(int x,int y){
    Square::xp=x;
    Square::yp=y;
    setRect(xp,yp,width=width,height=height);
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

void Square::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (game->pieceToPlace != nullptr){
        game->placePiece(this);

}



}
