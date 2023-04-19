#include "GameMode.h"
#include "Pieces.h"
#include "LanClient.h"
#include <QMessageBox>
GameMode::GameMode(Player player1,Player player2){
    this->player1 = player1;
    this->player2 = player2;
}
GameMode::GameMode()
{
 qDebug()<<"GameMode";


}

Player GameMode::getPlayer2() const
{
    return player2;
}

Player GameMode::getPlayer1() const
{
    return player1;
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
              qDebug()<<"King found";
          }
       }
       // for testing

       //for testing
       for(auto it=Piece::allFigures.begin();it!=piece->Piece::allFigures.end();it++)
       {
          if ((*it)!=nullptr){
              (*it)->getPossibleMoves();
          if(((*it)->getIsWhite()!=king->getIsWhite()) && ((*it)->movePossible(king->actualPosition)))
          {
              qDebug()<<"Krol zagrozony";
              return true;
          }

          }
\

       }
       qDebug()<<"Krol safe";
       return false;
   }
bool GameMode::isFinished(Piece *piece)
{
    std::string previousPose="00";
    std::string nextPose="00";
    for(auto it=Piece::allFigures.begin();it!=Piece::allFigures.end();it++)
    {
       if ((*it)->getIsWhite()==piece->getIsWhite()){
           qDebug()<<"Checking next piece";
           (*it)->getPossibleMoves();
                  for (const std::string& move :(*it)->allPossibleMoves) {
                       qDebug()<<"Checking next move";

                        previousPose=(*it)->actualPosition;
                        qDebug()<<"wodking";
                        (*it)->actualPosition=move;

                        // TUTAJ CRASH
                        if(!isMate(*it))
                        {
                            (*it)->actualPosition=previousPose;
                            qDebug()<<"krola uratuje sie";
                            return false;
                        }

                        //TUTAJ CRASH
                    }
                  (*it)->actualPosition=previousPose;

       }

    }
    return false;
    qDebug()<<"Zaden ruch nie pomoze";
    return true;
}
Singleplayer::Singleplayer(Player player1,Player player2){
       this->player1=player1;
       this->player2=player2;
       this->isGameStarted=true;
   }
void Singleplayer::swichTurn(){
    qDebug()<<"Singleplayer switch turn";
    activePlayer->getTimerWidget()->addTime(20);

    activePlayer->getTimerWidget()->getTimer()->stop();
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
    activePlayer->getTimerWidget()->getTimer()->start();

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
    this->player1=player1;
    activePlayer=&(this->player1);
    qDebug()<<"constructor active player"<<activePlayer->getIsWhite();
    client = new MyClient();
    client->connectToServer();
    connect(client,&MyClient::opponentMove,this,&Multiplayer::receivedMove);

}
Computer::Computer(Player player1)
{
    this->player1.setIsWhite(player1.getIsWhite());
    activePlayer=&(this->player1);
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
bool GameMode::movePiece(Piece* piece,int X,int Y)
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
           piece->actualPosition=secondarySquare;
           if(!isMate(piece)){
           std::cout<<"Secondary square"<< secondarySquare;
           piece->setX(chessboard->board.at(secondarySquare)->getX());
           piece->setY(chessboard->board.at(secondarySquare)->getY());
           piece->actualPosition=secondarySquare;
           chessboard->board.at(primarySquare)->piece=nullptr;
           chessboard->board.at(primarySquare)->setOccupied(false);
           chessboard->board.at(secondarySquare)->piece = piece;
           chessboard->board.at(secondarySquare)->setOccupied(true);
           std::cout << "moved" << "\n";
           return true;
           }
           else
           {
               piece->actualPosition=primarySquare;
               return false;
           }



}
bool GameMode::executeMove(Piece* piece, int X,int Y){

    std::string desiredSquare ="00";
    desiredSquare[0]=getColumnFromPixels(X);
    desiredSquare[1]=getRowFromPixels(Y);
    std::cout<<desiredSquare<<"\n";
    std::cout<<piece->movePossible(desiredSquare)<<"\n";
    qDebug()<<"Move possible" <<piece->movePossible(desiredSquare);

    if (piece->movePossible(desiredSquare))
    {
        qDebug()<<"ruch mozliwy";
        if (chessboard->board.at(desiredSquare)->isOccupied())
        {
            qDebug()<<"atakuje";
            if(attackPiece(piece,X,Y))
            {
            piece->changeFirstMove();
            return true;
            }
            else{
                return false;
            }
        }
        else
        {
            qDebug()<<"przenosze";
            if(movePiece(piece,X,Y))
            {
            piece->changeFirstMove();
            return true;
            }
            else{
                return false;
            }
        }
    }
    else{
        return false;
    }

}
bool GameMode::attackPiece(Piece* piece, int X,int Y)
     {
            std::string primarySquare = piece->actualPosition;
            std::string secondarySquare ="00";
            secondarySquare[0]=getColumnFromPixels(X);
            secondarySquare[1]=getRowFromPixels(Y);
            piece->actualPosition=secondarySquare;
            chessboard->board.at(secondarySquare)->piece->actualPosition = "00";
            if(!isMate(piece)){
         piece->setX(chessboard->board.at(secondarySquare)->getX());
         piece->setY(chessboard->board.at(secondarySquare)->getY());
         this->pieceToRemove=chessboard->board.at(secondarySquare)->piece;
         std::cout << "removed item" << "\n";
         piece->allFigures.remove(chessboard->board.at(secondarySquare)->piece);
         chessboard->board.at(secondarySquare)->piece = nullptr;
         chessboard->board.at(primarySquare)->piece=nullptr;
         chessboard->board.at(primarySquare)->setOccupied(false);
         chessboard->board.at(secondarySquare)->piece = piece;
         chessboard->board.at(secondarySquare)->setOccupied(true);
         return true;
            }else{
                piece->actualPosition=primarySquare;
                chessboard->board.at(secondarySquare)->piece->actualPosition = secondarySquare;

                return false;
            }

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

        qDebug()<<"active player"<<activePlayer->getIsWhite();
        if (this->activePlayer->getIsWhite()==chessboard->board.at(primarySquare)->piece->getIsWhite()) {
            if(isMate(chessboard->board.at(primarySquare)->piece))
            {
                if(!isFinished(chessboard->board.at(primarySquare)->piece)) {for(int i=0;i<=10;i++){qDebug() <<"No mvoes poossible";}}
                QMessageBox msgBox= QMessageBox();
                msgBox.setText("Mate, are you playing or want to surrender?");
                msgBox.addButton("Play", QMessageBox::AcceptRole);
                msgBox.addButton("Surrender", QMessageBox::RejectRole);

                int result = msgBox.exec();

                switch (result) {
                    case QMessageBox::AcceptRole:
                        // User clicked "Play"
                        qDebug() << "User clicked Play";
                        return chessboard->board.at(primarySquare)->piece;
                    case QMessageBox::RejectRole:
                        // User clicked "Quit"
                        qDebug() << "User clicked Quit";
                        emit this->quitGame();
                        break;
                    default:

                        qDebug() << "User closed the message box";

                        break;
                }
            }else return chessboard->board.at(primarySquare)->piece;


        }
        else
        {
            qDebug()<<"to nie twoj pionek";
            return nullptr;
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
    chooseFirst();
    return this->isGameStarted;
}

void Multiplayer::receivedMove(std::string move)
{
    qDebug()<<"move to perform"<<QString::fromStdString(move);
    std::string from = move.substr(0, 2);
    std::string to= move.substr(2,4);
    executeMove(chessboard->board.at(from)->piece,chessboard->board.at(to)->getX(),chessboard->board.at(to)->getY());
}

