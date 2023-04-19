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

public slots:
    void updateTime();
    void addTime(int seconds);

private:
    int timeRemaining;
    QGraphicsRectItem* frame;
    QGraphicsSimpleTextItem* label;
    QTimer* timer;
};



#endif // TIMER_H
