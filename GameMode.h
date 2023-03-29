#ifndef GAMEMODE_H
#define GAMEMODE_H
#include "Player.h"
#include "LanClient.h"
#include "Chessboard.h"

class GameMode{
public:
GameMode(Player player1,Player player2);
GameMode();
protected:
   Player player1;
   Player player2;
   Player* activePlayer;
   Board* chessboard;
public:

   void setChessboard(Board* chessboard);
   void chooseFirst();
   void start();
   void end();
   virtual void swichTurn()=0;
   virtual void opponentMove()=0;
   bool isMate(Board* board);

};

class Singleplayer : GameMode{
public:
    Singleplayer(Player player1,Player player2);
    virtual void swichTurn();
    virtual void opponentMove();
};
class Multiplayer : GameMode{
private:
    MyClient* client;
public:
    virtual void swichTurn();
    virtual void opponentMove();
};
class Computer : GameMode{
private:
    Computer* computer;
public:
    virtual void swichTurn();
    virtual void opponentMove();
};

#endif // GAMEMODE_H
