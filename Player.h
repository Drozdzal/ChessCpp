#ifndef PLAYER_H
#define PLAYER_H
#include "Timer.h"
#include "iostream"
#include <QString>
class Player
{
private:
    std::string name;
    bool isWhite;
    TimerWidget* timer;
public:
    Player();
    Player(std::string,bool);
    void setIsWhite(bool isWhite);
bool PlayerInDatabase();
void saveResultInDb();
bool getIsWhite();
std::string getName();
TimerWidget *getTimerWidget() const;
};

#endif // PLAYER_H
