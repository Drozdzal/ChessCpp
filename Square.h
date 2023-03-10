#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QObject>

class Square: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Square();
//public slots:
    void setPosition(int x,int y);
    void setColor(bool isWhite);
private:
    int xp;
    int yp;
    int width=75;
    int height=75;
    int row;
    int column;
    bool occupied;
    int occuping_piece;
    bool isWhite;

};


#endif // SQUARE_H
