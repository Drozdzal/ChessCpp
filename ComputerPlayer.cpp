#include "ComputerPlayer.h"
#include <QRandomGenerator>

void ComputerPlayer::setIsWhite(bool isWhite)
{
    this->isWhite=isWhite;
}

ComputerPlayer::ComputerPlayer(){

}
SimpleComputer::SimpleComputer(){
}
std::string SimpleComputer::getNextMove()
{
    QRandomGenerator generator = QRandomGenerator::securelySeeded();
    qDebug()<<"Getting next move";
    Piece* choosenPiece=nullptr;
    int choosenPieceId,choosenMoveId;
    int num_of_pieces,num_of_moves;
    std::string change="00I9";
    std::string choosenMove="I9";
    do{
//    choosenPieceId = std::rand() % Piece::allFigures.size();
    num_of_pieces=Piece::allFigures.size();
    choosenPieceId = generator.bounded(0, num_of_pieces);
    choosenPiece=*(std::next(Piece::allFigures.begin(), choosenPieceId));
    choosenPiece->getPossibleMoves();
    qDebug()<<"Wybieram pionek gdyz nie spelnia wymogow";
    qDebug()<<(choosenPiece->getIsWhite()==this->isWhite);
    }
    while((choosenPiece->allPossibleMoves.size()<2) || (choosenPiece->getIsWhite()!=this->isWhite));
    change[0]=choosenPiece->actualPosition[0];
    change[1]=choosenPiece->actualPosition[1];
    bool movePossible=false;
    do{
    num_of_moves=choosenPiece->allPossibleMoves.size();
    choosenMoveId = generator.bounded(0, num_of_moves);
    choosenMove=*(std::next(choosenPiece->allPossibleMoves.begin(), choosenMoveId));
    qDebug()<<"Wybrany ruch"<<QString::fromStdString(choosenMove);
    qDebug()<<int(char("H"));
    qDebug()<<QString::number(int(choosenMove[0])<=72);
    qDebug()<<QString::number(int(choosenMove[0])>=65);
//    qDebug()<<int(choosenMove[0])>=int("A");


    if((int(choosenMove[0])<=72) && (int(choosenMove[0])>=65))
    {
        if(((choosenMove[1]-'0')>=1) && ((choosenMove[1]-'0')<=8) )
        {
            change[2]=choosenMove[0];
            change[3]=choosenMove[1];
            qDebug()<<"Ruch wybrany";
            movePossible=true;
        }
    }
    qDebug()<<"Wybieram ruch pionka";
    }
    while(!movePossible);
    qDebug()<<"Komputer wybral ruch" <<change[2]<<change[3];

    return change;

}

