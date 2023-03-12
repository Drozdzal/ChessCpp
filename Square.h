#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>

class Square: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Square();
//public slots:
    void setPosition(int x,int y);
    void setColor(bool isWhite);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int xp;
    int yp;
    int row;
    int column;
private:
    int width=75;
    int height=75;
    bool occupied;
    int occuping_piece;
    bool isWhite;

};


#endif // SQUARE_H
