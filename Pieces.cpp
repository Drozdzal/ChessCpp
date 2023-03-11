#include "Pieces.h"
#include <QGraphicsScene>
#include <QList>
#include "Game.h"

extern Game * game; // there is an external global object called game

Piece::Piece(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // draw graphics
    setPixmap(QPixmap(":/bazowy/bialy_krol.png").scaled(75,75));
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (game->pieceToPlace == nullptr){
            game->pickUpPiece(this);
    }
//    else if (getIsPicked()==true){
//        game->placePiece(this);
//        setIsPicked(false);
//    }
}

bool Piece::getIsWhite(){
    return isWhite;
}


bool Piece::getIsPicked(){
    return isPicked;
}

void Piece::setIsPicked(bool picked_state){
    isPicked=picked_state;
}
