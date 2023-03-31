#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "Pieces.h"
#include "Player.h"
class ComputerPlayer{
protected:
    std::string name;
    bool isWhite;
public:
    ComputerPlayer();
    virtual std::string getNextMove()=0;
    void setIsWhite(bool isWhite);
};

class SimpleComputer: public ComputerPlayer{
public:
    SimpleComputer();
    virtual std::string getNextMove();

};

#endif // COMPUTERPLAYER_H
