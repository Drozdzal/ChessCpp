#ifndef TIMER_H
#define TIMER_H
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QTimer>
#include <QTime>
#include <QPointF>
#include <QFont>
#include <QPen>
#include <QBrush>

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

class TimerWidget : public QGraphicsTextItem {
public:
    TimerWidget(QGraphicsItem* parent = nullptr);

public slots:
    void updateTime();
    void addTime(int seconds);

private:
    int timeRemaining;
    QGraphicsRectItem* frame;
    QGraphicsSimpleTextItem* label;
};



#endif // TIMER_H
