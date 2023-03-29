#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    void setTime();
    void getTime();
    void addBonus();
private:
    int secondsToEnd;
    int bonusPerRound;

};

#endif // TIMER_H
