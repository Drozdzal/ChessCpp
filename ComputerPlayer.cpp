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
    int choosenPieceId;
    int num_of_pieces;
    do{
//    choosenPieceId = std::rand() % Piece::allFigures.size();
    num_of_pieces=Piece::allFigures.size();
    choosenPieceId = generator.bounded(0, num_of_pieces);
    choosenPiece=*(std::next(Piece::allFigures.begin(), choosenPieceId));
    choosenPiece->getPossibleMoves();
    qDebug()<<choosenPiece->allPossibleMoves.size();
    qDebug()<<(choosenPiece->getIsWhite()==this->isWhite);
    }
    while((choosenPiece->allPossibleMoves.size()<1) || (choosenPiece->getIsWhite()!=this->isWhite));
//    int choosenMoveId = std::rand() % choosenPiece->allPossibleMoves.size();
//    std::string choosenMove=(*std::next(choosenPiece->allPossibleMoves.begin(), choosenMoveId));
    std::string change="0000";
//    if(choosenPiece!=nullptr)
//    {
//    change[0]=choosenPiece->actualPosition[0];
//    change[1]=choosenPiece->actualPosition[1];
//    }
//    change[2]=choosenMove[0];
//    change[3]=choosenMove[1];
//    std::cout << change <<"\n";
    change="A2A3";
    return change;

}

