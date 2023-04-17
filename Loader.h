#ifndef LOADER_H
#define LOADER_H
#include "iostream"

#include "Pieces.h"
#include "Chessboard.h"
class Loader{
public:
    void readJson(QString path);
    void firstMoveFromJson(Board* board);
    void moveForward(Board* board);
    void moveBackward(Board* board);
    void createPieces(Board* board,QJsonObject obiekcik);
    int actual_move=0;
private:
    QString loadedGame;

};

#endif // LOADER_H


