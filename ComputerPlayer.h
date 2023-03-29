#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "Chessboard.h"
class ComputerPlayer{
private:
    std::string name;
    bool isWhite;
    Board* chessboard;
public:
    virtual std::string getNextMove()=0;
};

class SingleComputer:ComputerPlayer{
public:
    virtual std::string getNextMove();

};

#endif // COMPUTERPLAYER_H
