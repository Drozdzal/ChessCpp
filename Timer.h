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
#include <QString>

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
    TimerWidget(QString name,QGraphicsItem* parent = nullptr);

    QTimer *getTimer() const;

    void setTimeRules(int fullTime,int addingTime);

public slots:
    void updateTime();
    void addTime();

private:
    int timeRemaining=600;
    int timeAdding=20;
    QGraphicsRectItem* frame;
    QGraphicsSimpleTextItem* label;
    QTimer* timer;
};



#endif // TIMER_H
