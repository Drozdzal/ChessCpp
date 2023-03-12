#include "Pieces.h"
#include <QGraphicsScene>
#include <QList>
#include "Game.h"

extern Game * game; // there is an external global object called game

Piece::Piece(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // draw graphics
//    setPixmap(QPixmap(":/bazowy/bialy_krol.png").scaled(75,75));
    setPixmap(QPixmap(":/bazowy/bialy_pionek.png").scaled(75,75));
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

bool Piece::checkPawnMoves(int destRow,int destColumn){
    if (this->column-destColumn==1 && this->row-destRow==0){
            return true;
    }
    else{
        return false;
    }
}

bool Piece::checkKingMoves(int destRow,int destColumn){
    if (abs(this->column-destColumn)<=1 &&  abs(this->row-destRow)<=1) {
            return true;
    }
    else{
        return false;
    }
}

bool Piece::checkRookMoves(int destRow,int destColumn)
{
    if (abs(this->column-destColumn)==0 ||  abs(this->row-destRow)==0) {
            return true;
    }
    else{
        return false;
    }
}


bool Piece::checkBishopMoves(int destRow,int destColumn)
{
    if (abs(this->column-destColumn) ==  abs(this->row-destRow)) {
            return true;
    }
    else{
        return false;
    }
}

bool Piece::checkKnightMoves(int destRow,int destColumn)
{
    if ((abs(this->column-destColumn) >=1 && abs(this->column-destColumn) <=2)  &&
            (abs(this->row-destRow)>=1 && abs(this->row-destRow)<=2) &&
            ((abs(this->row-destRow)+abs(this->column-destColumn))==3)) {
            return true;
    }
    else{
        return false;
    }
}

bool Piece::isMovePossible(int destRow,int destColumn){
    if (this->firstMove){
        this->firstMove=false;
        return true;
    }
    else{
    return this->checkKnightMoves(destRow,destColumn);
    }
}

//void createWhitePiece(){
//    this.setPixmap(QPixmap(":/bazowy/bialy_pionek.png").scaled(75,75));


//}
