#include "Player.h"
Player::Player()
{

}
Player::Player(std::string name,bool isWhite)
{
    this->name=name;
    this->isWhite=isWhite;
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
