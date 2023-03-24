#ifndef LOADER_H
#define LOADER_H
#include "iostream"

#include "Pieces.h"

class Loader{
public:
    void readJson(QString path);
    void firstMoveFromJson();
    void moveForward();
    void moveBackward();
    int actual_move=0;
private:
    QString loadedGame;

};

#endif // LOADER_H


