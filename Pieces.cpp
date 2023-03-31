#include "Pieces.h"
#include <QGraphicsScene>
#include <QList>
#include "Game.h"
#include <iostream>

extern Game * game; // there is an external global object called game
std::list<Piece*> Piece::allFigures{};

Piece::Piece(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    allFigures.push_back(this);
}


void Piece::changeFirstMove()
{
    firstMove=false;
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

bool Piece::movePossible(std::string desiredSquare)
{
    if (allPossibleMoves.empty())
    {
        getPossibleMoves();
    }
    bool found = (std::find(allPossibleMoves.begin(), allPossibleMoves.end(), desiredSquare) != allPossibleMoves.end());
    return found;
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
void Piece::getPossibleMoves()
{

}

void Pawn::getPossibleMoves()
{
    int goForward;
    char column,row;
    column = actualPosition[0];
    row = actualPosition[1];


    if (getIsWhite()) {
                    goForward=1;
                }
                else {
                goForward=-1;
                }

                    possiblePosition[0]=column;
                    possiblePosition[1]=(char)((int)row-1*goForward);
                    if (!isSquareOccupied(possiblePosition)) {
                        allPossibleMoves.push_front(possiblePosition);
                    }
                    possiblePosition[0]=column;
                    possiblePosition[1]=(char)((int)row-2*goForward);

                    if (getFirstMove() && (!isSquareOccupied(possiblePosition))) {

                        allPossibleMoves.push_front(possiblePosition);
                    }


                    possiblePosition[0]=(char)((int)(column)-1);
                    possiblePosition[1]=(char)((int)row-1*goForward);
                    if (isSquareOccupied(possiblePosition))
                    {
                        allPossibleMoves.push_front(possiblePosition);
                    }

                    possiblePosition[0]=(char)((int)(column)+1);
                    possiblePosition[1]=(char)((int)row-1*goForward);
                    if (isSquareOccupied(possiblePosition))
                    {
                        allPossibleMoves.push_front(possiblePosition);
                    }
}


Knight::Knight(bool isWhite){
    this->isWhite=isWhite;
    if (isWhite){
        this->setPixmap(QPixmap(":/bazowy/bialy_goniec.png").scaled(75,75));
    }
    else{
        this->setPixmap(QPixmap(":/bazowy/czarny_goniec.png").scaled(75,75));
    }
}

void Knight::getPossibleMoves()
{

    int goForward;
    char column,row;
    column = actualPosition[0];
    row = actualPosition[1];
    for(int i=-1;i<2;i+=2) {
                goForward=i;
                possiblePosition[0]=(char) ((int) (column) - 1*goForward);
                possiblePosition[1]=(char) (row - 2 * goForward);
                allPossibleMoves.push_front(possiblePosition);
                possiblePosition[0]=(char) ((int) (column) - 2*goForward);
                possiblePosition[1]=(char) (row - 1 * goForward);
                allPossibleMoves.push_front(possiblePosition);
                possiblePosition[0]=(char) ((int) (column) - 1*goForward);
                possiblePosition[1]=(char) (row + 2 * goForward);
                allPossibleMoves.push_front(possiblePosition);
                possiblePosition[0]=(char) ((int) (column) - 2*goForward);
                possiblePosition[1]=(char) (row + 1 * goForward);
                allPossibleMoves.push_front(possiblePosition);

            }
}


Bishop::Bishop(bool isWhite){
    this->isWhite=isWhite;
    if (isWhite){
        this->setPixmap(QPixmap(":/bazowy/bialy_skoczek.png").scaled(75,75));
    }
    else{
        this->setPixmap(QPixmap(":/bazowy/czarny_skoczek.png").scaled(75,75));
    }
}


void Bishop::getPossibleMoves()
{

    char column,row;
    column = actualPosition[0];
    row = actualPosition[1];
    for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column)-1*i);
                possiblePosition[1]=(char)(row-1*i);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }

            for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column)+1*i);
                possiblePosition[1]=(char)(row-1*i);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }


            for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column)-1*i);
                possiblePosition[1]=(char)(row+1*i);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }


            for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column)+1*i);
                possiblePosition[1]=(char)(row+1*i);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }
}

Rook::Rook(bool isWhite){
    this->isWhite=isWhite;
    if (isWhite){
        this->setPixmap(QPixmap(":/bazowy/bialy_wieza.png").scaled(75,75));
    }
    else{
        this->setPixmap(QPixmap(":/bazowy/czarny_wieza.png").scaled(75,75));
    }
}

void Rook::getPossibleMoves()
{

    char column,row;
    column = actualPosition[0];
    row = actualPosition[1];
    for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column));
                possiblePosition[1]=(char)(row-1*i);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }

            for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column)-1*i);
                possiblePosition[1]=(char)(row);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }


            for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column)+1*i);
                possiblePosition[1]=(char)(row);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }


            for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column));
                possiblePosition[1]=(char)(row+1*i);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }
}


King::King(bool isWhite){
    this->isWhite=isWhite;
    if (isWhite){
        this->setPixmap(QPixmap(":/bazowy/bialy_krol.png").scaled(75,75));
    }
    else{
        this->setPixmap(QPixmap(":/bazowy/czarny_krol.png").scaled(75,75));
    }
}

void King::getPossibleMoves()
{

    char column,row;
    column = actualPosition[0];
    row = actualPosition[1];
    for(int i=-1; i<=1;i++)
        for(int j=-1; j<=1;j++)
            {

                possiblePosition[0]=(char)((int)(column)-1*i);
                possiblePosition[1]=(char)(row-1*j);
                for(auto it=Piece::allFigures.begin();it!=Piece::allFigures.end();it++)
                {
                   if(((*it)->getIsWhite()!=this->getIsWhite()) && ((*it)->movePossible(this->actualPosition)))
                   {
                       allPossibleMoves.push_front(possiblePosition);
                   }
                }


            }

}


Queen::Queen(bool isWhite){
    this->isWhite=isWhite;
    if (isWhite){
        this->setPixmap(QPixmap(":/bazowy/bialy_hetman.png").scaled(75,75));
    }
    else{
        this->setPixmap(QPixmap(":/bazowy/czarny_hetman.png").scaled(75,75));
    }
}

void Queen::getPossibleMoves()
{

    char column,row;
    column = actualPosition[0];
    row = actualPosition[1];
    for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column)-1*i);
                possiblePosition[1]=(char)(row-1*i);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }

            for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column)+1*i);
                possiblePosition[1]=(char)(row-1*i);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }


            for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column)-1*i);
                possiblePosition[1]=(char)(row+1*i);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }


            for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column)+1*i);
                possiblePosition[1]=(char)(row+1*i);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }

    for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column));
                possiblePosition[1]=(char)(row-1*i);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }

            for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column)-1*i);
                possiblePosition[1]=(char)(row);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }


            for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column)+1*i);
                possiblePosition[1]=(char)(row);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }


            for(int i=1; i<=7;i++)
            {

                possiblePosition[0]=(char)((int)(column));
                possiblePosition[1]=(char)(row+1*i);
                allPossibleMoves.push_front(possiblePosition);
                if (isSquareOccupied(possiblePosition))
                {
                    break;
                }
            }
}

