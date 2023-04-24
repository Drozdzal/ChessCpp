#include "Timer.h"


    void Timer::setTime(){

    }
    void Timer::getTime(){

    }
    void Timer::addBonus(){

    }


    TimerWidget::TimerWidget(QString name=QString("Unknowed"),QGraphicsItem* parent)
        : QGraphicsTextItem(parent)
    {



        setPlainText("--:--");

          // set position to (800, 800)
          setPos(900, 100);

          // create timer to update the time every second
          timer = new QTimer(this);
          connect(timer, &QTimer::timeout, this, &TimerWidget::updateTime);
          timer->start(1000);

          // create gray frame
          QGraphicsRectItem* frame = new QGraphicsRectItem(0, 0, 70, 30, this);
          frame->setPen(QPen(Qt::gray));
          frame->setBrush(QBrush(Qt::lightGray));
          frame->setBrush(Qt::transparent);

          // create text above the timer
          QGraphicsTextItem* playerText = new QGraphicsTextItem(name, this);
          playerText->setDefaultTextColor(Qt::black);
          playerText->setFont(QFont("Arial", 14, QFont::Bold));
          playerText->setPos(-20, -30);
    }

 \
    void TimerWidget::updateTime()
    {
        timeRemaining--;
        if (timeRemaining < 0) {
            timeRemaining = 0;
        }
        int minutes = timeRemaining / 60;
        int seconds = timeRemaining % 60;
        setPlainText(QString("%1:%2").arg(minutes, 2, 10, QChar('0'))
                                      .arg(seconds, 2, 10, QChar('0')));
    }

    void TimerWidget::addTime()
    {
        timeRemaining += timeAdding;
    }

    void TimerWidget::setTimeRules(int newTimeRemaining,int addingTime)
    {
        this->timeRemaining = newTimeRemaining*60;
        this->timeAdding=addingTime;

    }

    QTimer *TimerWidget::getTimer() const
    {
        return timer;
    }
