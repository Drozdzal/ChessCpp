#ifndef PLAYER_H
#define PLAYER_H
#include "Timer.h"
#include "iostream"
class Player
{
private:
    std::string name;
    bool isWhite;
    Timer timer;
public:
    Player();
    Player(std::string,bool);
bool PlayerInDatabase();
void saveResultInDb();
void setIsWhite(bool isWhite);
bool getIsWhite();
std::string getName();
};

#endif // PLAYER_H
