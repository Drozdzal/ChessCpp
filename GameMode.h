#ifndef GAMEMODE_H
#define GAMEMODE_H
#include <QObject>
#include "Player.h"
#include "LanClient.h"
#include "Chessboard.h"
#include "ComputerPlayer.h"

class GameMode: public QObject{
    Q_OBJECT
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
   std::string currentChange="0000";
public:
   bool gameStarted();
   void setChessboard(Board* chessboard);
   void chooseFirst();
   void start();
   void end();
   virtual void swichTurn()=0;
   virtual void opponentMove()=0;
   bool isMate(Piece* piece);
   bool isFinished(Piece* piece);
   void pieceDeleted();
   Piece* isPieceToDelete();


   bool executeMove(Piece* piece, int X,int Y);
   bool piecesOnPath(Square *choosenSquare);
   void setPickedPiece();
   void changeTurn();
   bool movePiece(Piece* piece,int X,int Y);
   bool attackPiece(Piece* piece,int X,int Y);

   Piece* canPickPiece(int X,int Y);
   char getColumnFromPixels(int X);
   char getRowFromPixels(int Y);
   int getSquareOnRowColumn(int row,int column);
signals:
   void quitGame();


};

class Singleplayer : public GameMode{
    Q_OBJECT
public:
    Singleplayer(Player player1,Player player2);
    void swichTurn() override;
    void opponentMove() override;
};
class Multiplayer : public GameMode{
    Q_OBJECT
private:
    MyClient* client;
public:
    Multiplayer(Player player1);
    void swichTurn() override;
    void opponentMove() override;
public slots:
    void receivedMove(std::string move);
};
class Computer : public GameMode{
    Q_OBJECT
private:
    SimpleComputer* computer;
public:
    Computer(Player player1);
    void swichTurn() override;
    void opponentMove() override;
};

#endif // GAMEMODE_H
