#include "GameMode.h"

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
    if (player1First)
    {
        activePlayer=&player1;
    }
    else
    {
        activePlayer=&player2;
    }
}
void GameMode::start(){
}
void GameMode::end(){
}
   bool GameMode::isMate(Board* board){
       return false;
   }

   Singleplayer::Singleplayer(Player player1,Player player2){
       this->player1=player1;
       this->player2=player2;
   }
void Singleplayer::swichTurn(){
}
     void Singleplayer::opponentMove(){
}

     void Multiplayer::swichTurn(){
}
     void Multiplayer::opponentMove(){
}


     void Computer::swichTurn(){
}
     void Computer::opponentMove(){
}
