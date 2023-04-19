#include "Player.h"
TimerWidget *Player::getTimerWidget() const
{
    return timer;
}

Player::Player()
{

}
Player::Player(std::string name,bool isWhite)
{
    this->name=name;
    this->isWhite=isWhite;
    timer=new TimerWidget(QString::fromStdString(name));
}
bool Player::PlayerInDatabase(){
    return true;
}
void Player::saveResultInDb(){

}
bool Player::getIsWhite(){
return this->isWhite;
}
std::string Player::getName()
{
    return "tak";
}

void Player::setIsWhite(bool isWhite)
{
    this->isWhite=isWhite;
}
