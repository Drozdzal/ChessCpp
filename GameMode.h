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
   bool isGameStarted;
   Piece* pieceToRemove=nullptr;
public:
   bool gameStarted();
   void setChessboard(Board* chessboard);
   void chooseFirst();
   void start();
   void end();
   virtual void swichTurn()=0;
   virtual void opponentMove()=0;
   bool isMate(Piece* piece);
   void pieceDeleted();
   Piece* isPieceToDelete();


   bool executeMove(Piece* piece, int X,int Y);
   bool piecesOnPath(Square *choosenSquare);
   void setPickedPiece();
   void changeTurn();
   void movePiece(Piece* piece,int X,int Y);
   void attackPiece(Piece* piece,int X,int Y);

   Piece* canPickPiece(int X,int Y);
   char getColumnFromPixels(int X);
   char getRowFromPixels(int Y);
   int getSquareOnRowColumn(int row,int column);



};

class Singleplayer : public GameMode{
public:
    Singleplayer(Player player1,Player player2);
    virtual void swichTurn();
    virtual void opponentMove();
};
class Multiplayer : public GameMode{
private:
    MyClient* client;
public:
    virtual void swichTurn();
    virtual void opponentMove();
};
class Computer : public GameMode{
private:
    Computer* computer;
public:
    virtual void swichTurn();
    virtual void opponentMove();
};

#endif // GAMEMODE_H
