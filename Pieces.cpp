#include "Pieces.h"
#include <QGraphicsScene>
#include <QList>
#include "Game.h"
#include <iostream>
#include "Pieces.h"

extern Game * game; // there is an external global object called game
std::list<Piece*> Piece::allFigures{};

Piece::Piece(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    allFigures.push_back(this);
}



bool Piece::getIsWhite(){
    return isWhite;
}



bool Piece::isSquareOccupied(std::string desiredSquare)
{
    for(auto it = allFigures.begin(); it != allFigures.end(); it++){

    if (desiredSquare==(*it)->actualPosition)
    {
        return true;
    }
    }
    return false;
}

bool Piece::getFirstMove()
{
    return this->firstMove;
}

Pawn::Pawn(bool isWhite){
    this->isWhite=isWhite;
    if (isWhite){
        this->setPixmap(QPixmap(":/bazowy/bialy_pionek.png").scaled(75,75));
    }
    else{
        this->setPixmap(QPixmap(":/bazowy/czarny_pionek.png").scaled(75,75));
    }
}

//bool Pawn::isMovePossible(int destRow, int destColumn){
//    if (this->getFirstMove()){
//        this->firstMove=false;
//        return true;
//    }
//    else{
//        if (this->column-destColumn==1 && this->row-destRow==0){
//                return true;
//        }
//        else{
//            return false;
//        }
//    }
//}

Knight::Knight(bool isWhite){
    this->isWhite=isWhite;
    if (isWhite){
        this->setPixmap(QPixmap(":/bazowy/bialy_goniec.png").scaled(75,75));
    }
    else{
        this->setPixmap(QPixmap(":/bazowy/czarny_goniec.png").scaled(75,75));
    }
}

//bool Knight::isMovePossible(int destRow, int destColumn){
//    if ((abs(this->column-destColumn) >=1 && abs(this->column-destColumn) <=2)  &&
//            (abs(this->row-destRow)>=1 && abs(this->row-destRow)<=2) &&
//            ((abs(this->row-destRow)+abs(this->column-destColumn))==3)) {
//            return true;
//    }
//    else{
//        return false;
//    }
//}


Bishop::Bishop(bool isWhite){
    this->isWhite=isWhite;
    if (isWhite){
        this->setPixmap(QPixmap(":/bazowy/bialy_skoczek.png").scaled(75,75));
    }
    else{
        this->setPixmap(QPixmap(":/bazowy/czarny_skoczek.png").scaled(75,75));
    }
}

//bool Bishop::isMovePossible(int destRow, int destColumn){
//    if (abs(this->column-destColumn) ==  abs(this->row-destRow)) {
//            return true;
//    }
//    else{
//        return false;
//    }
//}

Rook::Rook(bool isWhite){
    this->isWhite=isWhite;
    if (isWhite){
        this->setPixmap(QPixmap(":/bazowy/bialy_wieza.png").scaled(75,75));
    }
    else{
        this->setPixmap(QPixmap(":/bazowy/czarny_wieza.png").scaled(75,75));
    }
}

//bool Rook::isMovePossible(int destRow, int destColumn){
//    if (abs(this->column-destColumn)==0 ||  abs(this->row-destRow)==0) {
//            return true;
//    }
//    else{
//        return false;
//    }
//}

King::King(bool isWhite){
    this->isWhite=isWhite;
    if (isWhite){
        this->setPixmap(QPixmap(":/bazowy/bialy_krol.png").scaled(75,75));
    }
    else{
        this->setPixmap(QPixmap(":/bazowy/czarny_krol.png").scaled(75,75));
    }
}

//bool King::isMovePossible(int destRow, int destColumn){
//    if (abs(this->column-destColumn)<=1 &&  abs(this->row-destRow)<=1) {
//            return true;
//    }
//    else{
//        return false;
//    }
//}

Queen::Queen(bool isWhite){
    this->isWhite=isWhite;
    if (isWhite){
        this->setPixmap(QPixmap(":/bazowy/bialy_hetman.png").scaled(75,75));
    }
    else{
        this->setPixmap(QPixmap(":/bazowy/czarny_hetman.png").scaled(75,75));
    }
}

//bool Queen::isMovePossible(int destRow, int destColumn){
//    if (abs(this->column-destColumn)==0 ||  abs(this->row-destRow)==0 || (abs(this->column-destColumn) ==  abs(this->row-destRow)))  {
//            return true;
//    }
//    else{
//        return false;
//    }
//}
