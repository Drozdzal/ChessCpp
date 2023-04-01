#include "GameMode.h"
#include "Pieces.h"
#include "LanClient.h"

GameMode::GameMode(Player player1,Player player2){
    this->player1 = player1;
    this->player2 = player2;
}
GameMode::GameMode()
{

}
void GameMode::setChessboard(Board *chessboard)
{
    this->chessboard=chessboard;
}
void GameMode::chooseFirst(){
    bool player1First= std::rand()%2;
    qDebug()<<"Choosing first player";
    if (player1First)
    {
        qDebug()<<"First player player1";
        activePlayer=&player1;

    }
    else
    {
        qDebug()<<"First player player2";
        activePlayer=&player2;

    }
}




void GameMode::start(){
}
void GameMode::end(){
}
bool GameMode::isMate(Piece* piece){
       Piece* king=nullptr;
       //finding a king
       for(auto it=Piece::allFigures.begin();it!=piece->Piece::allFigures.end();it++)
       {
          if ((*it)->getIsWhite()==piece->getIsWhite()&&
               typeid(**it).name()==typeid(King).name()){
              king=(*it);
          }
       }

       for(auto it=Piece::allFigures.begin();it!=piece->Piece::allFigures.end();it++)
       {
          if ((*it)!=nullptr){
// COS TA PETLA PSUJE
//          if(((*it)->getIsWhite()!=king->getIsWhite()) && ((*it)->movePossible(king->actualPosition)))
//          {
//              qDebug()<<"Krol zagrozony";
//              return true;
//          }
          }
          else{
                   qDebug()<<"Nie sprawdzam";
          }

       }

       return false;
   }
Singleplayer::Singleplayer(Player player1,Player player2){
       this->player1=player1;
       this->player2=player2;
       this->isGameStarted=true;
   }
void Singleplayer::swichTurn(){
    qDebug()<<"Singleplayer switch turn";
    if (activePlayer==&player1)
    {
        qDebug()<<"pl1changing to 2";
        activePlayer=&player2;
    }
    else if(activePlayer==&player2)
    {
        activePlayer=&player1;
        qDebug()<<"pl2changing to 1";
    }
}
void Singleplayer::opponentMove(){
}
void Multiplayer::swichTurn(){
    client->sendMessage(this->currentChange);
    qDebug()<<"Multiplayer switch turn";

}
void Multiplayer::opponentMove(){
}
Multiplayer::Multiplayer(Player player1)
{
    qDebug()<<"construktor invoked";
    activePlayer=&player1;
    qDebug()<<"constructor active player"<<activePlayer->getIsWhite();
    client = new MyClient();
    client->connectToServer();
    connect(client,&MyClient::opponentMove,this,&Multiplayer::receivedMove);

}

Computer::Computer(Player player1)
{
    activePlayer=&player1;
    computer= new SimpleComputer();
    computer->setIsWhite(false);
}
void Computer::swichTurn(){
    std::string currentChange="0000";
    currentChange=computer->getNextMove();
    std::string primarySquare="00";
    primarySquare[0] = currentChange[0];
    primarySquare[1] = currentChange[1];
    Piece* piece=chessboard->board.at(primarySquare)->piece;
    std::string secondarySquare ="00";
    std::cout<<"Primary square"<< primarySquare;
    secondarySquare[0]=currentChange[2];
    secondarySquare[1]=currentChange[3];
    std::cout<<"Secondary square"<< secondarySquare;
    piece->setX(chessboard->board.at(secondarySquare)->getX());
    piece->setY(chessboard->board.at(secondarySquare)->getY());
    piece->actualPosition=secondarySquare;
    chessboard->board.at(primarySquare)->piece=nullptr;
    chessboard->board.at(primarySquare)->setOccupied(false);
    chessboard->board.at(secondarySquare)->piece = piece;
    chessboard->board.at(secondarySquare)->setOccupied(true);
    std::cout << "moved" << "\n";

}
void Computer::opponentMove(){
}
void GameMode::movePiece(Piece* piece,int X,int Y)
     {
           std::string primarySquare = piece->actualPosition;
           std::string secondarySquare ="00";
           currentChange[0]=primarySquare[0];
           currentChange[1]=primarySquare[1];
           std::cout<<"Primary square"<< primarySquare;
           secondarySquare[0]=getColumnFromPixels(X);
           secondarySquare[1]=getRowFromPixels(Y);
           currentChange[2]=getColumnFromPixels(X);
           currentChange[3]=getRowFromPixels(Y);
           std::cout<<"Secondary square"<< secondarySquare;
           piece->setX(chessboard->board.at(secondarySquare)->getX());
           piece->setY(chessboard->board.at(secondarySquare)->getY());
           piece->actualPosition=secondarySquare;
           chessboard->board.at(primarySquare)->piece=nullptr;
           chessboard->board.at(primarySquare)->setOccupied(false);
           chessboard->board.at(secondarySquare)->piece = piece;
           chessboard->board.at(secondarySquare)->setOccupied(true);
           std::cout << "moved" << "\n";



}
bool GameMode::executeMove(Piece* piece, int X,int Y){

    std::string desiredSquare ="00";
    desiredSquare[0]=getColumnFromPixels(X);
    desiredSquare[1]=getRowFromPixels(Y);
    std::cout<<desiredSquare<<"\n";
    std::cout<<piece->movePossible(desiredSquare)<<"\n";
    qDebug()<<"Move possible" <<piece->movePossible(desiredSquare);
    //if ((piece->movePossible(desiredSquare)) && (!isMate(piece)))
    piece->getPossibleMoves();
    if (piece->movePossible(desiredSquare))
    {
        qDebug()<<"ruch mozliwy";
        if (chessboard->board.at(desiredSquare)->isOccupied())
        {
            qDebug()<<"atakuje";
            attackPiece(piece,X,Y);
            piece->getPossibleMoves();
            return true;
        }
        else
        {
            qDebug()<<"przenosze";
            movePiece(piece,X,Y);
            piece->getPossibleMoves();
            return true;
        }
    }
    else{
        return false;
    }

}
void GameMode::attackPiece(Piece* piece, int X,int Y)
     {
            std::string primarySquare = piece->actualPosition;
            std::string secondarySquare ="00";
            secondarySquare[0]=getColumnFromPixels(X);
            secondarySquare[1]=getRowFromPixels(Y);
         piece->setX(chessboard->board.at(secondarySquare)->getX());
         piece->setY(chessboard->board.at(secondarySquare)->getY());
         piece->actualPosition=secondarySquare;
//         chessboard->board.at(secondarySquare)->piece->actualPosition="00";
//         window->deletePiece(chessboard.board.at(secondarySquare)->piece);
         this->pieceToRemove=chessboard->board.at(secondarySquare)->piece;
         std::cout << "removed item" << "\n";
         chessboard->board.at(secondarySquare)->piece = nullptr;
         piece->allFigures.remove(chessboard->board.at(secondarySquare)->piece);
         chessboard->board.at(primarySquare)->piece=nullptr;
         chessboard->board.at(primarySquare)->setOccupied(false);
         chessboard->board.at(secondarySquare)->piece = piece;
         chessboard->board.at(secondarySquare)->setOccupied(true);
     }
Piece* GameMode::isPieceToDelete()
{
    return this->pieceToRemove;
}
void GameMode::pieceDeleted()
{
    this->pieceToRemove=nullptr;
}
int GameMode::getSquareOnRowColumn(int row,int column){
         return (row-1)*8+(column-1);
     }
Piece* GameMode::canPickPiece(int X,int Y)
{
    std::string primarySquare="00";
    primarySquare[0]=getColumnFromPixels(X);
    primarySquare[1]=getRowFromPixels(Y);
    qDebug()<<"can pick " << activePlayer->getIsWhite();
    if (chessboard->board.at(primarySquare)->piece !=nullptr )
    {
        if (/*!isMate(chessboard->board.at(primarySquare)->piece)*/ true){
        qDebug()<<"active player"<<activePlayer->getIsWhite();
        if (this->activePlayer->getIsWhite()==chessboard->board.at(primarySquare)->piece->getIsWhite()) return chessboard->board.at(primarySquare)->piece;
        else return nullptr;
    }
    }
    else
    {
        return nullptr;
    }

}
char GameMode::getRowFromPixels(int X)

{
    int row= 1+(X-chessboard->boardRowOffset)/chessboard->sizeOfSquare;
    return (row+'0');
}
char GameMode::getColumnFromPixels(int Y)
{
    int asciAdd=(Y-chessboard->boardColumnOffset)/chessboard->sizeOfSquare;
    return ((char)(65+asciAdd));
}

bool GameMode::gameStarted()
{
//    chooseFirst();
    return this->isGameStarted;
}

void Multiplayer::receivedMove(std::string move)
{
    qDebug()<<"move to perform"<<QString::fromStdString(move);
    std::string from = move.substr(0, 2);
    std::string to= move.substr(2,4);
    executeMove(chessboard->board.at(from)->piece,chessboard->board.at(to)->getX(),chessboard->board.at(to)->getY());
}
